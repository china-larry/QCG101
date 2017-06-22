#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comm.h"
#include <QDebug>
//toLatin1
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //
    m_pFlagPushButton = new QPushButton("蜂鸣器", this);
    m_pFlagPushButton->move(30, 50);
    connect(m_pFlagPushButton, SIGNAL(clicked(bool)), this, SLOT(SlotCheckButton()));
    //
    m_pDCOpenPushButton = new QPushButton("直流电机开", this);
    m_pDCOpenPushButton->move(150, 50);
    connect(m_pDCOpenPushButton, SIGNAL(clicked(bool)), this, SLOT(SlotDCOpenButton()));
    //
    m_pDCClosePushButton = new QPushButton("直流电机关", this);
    m_pDCClosePushButton->move(270, 50);
    connect(m_pDCClosePushButton, SIGNAL(clicked(bool)), this, SLOT(SlotDCCloseButton()));
    //
    initSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotReadSerial()
{
    if(m_pSerialPort->bytesAvailable() < 0)
    {
        qDebug() << "not data";
        return;
    }
    QByteArray qa = m_pSerialPort->readAll();
    qDebug() << "size: " << qa.size() << qa;
}

void MainWindow::SlotCheckButton()
{
            QString qstrData = "23 23 00 A7 00 00 00 00 00 00 00 00 2F 0D 0A";
            bool ok;
            QByteArray qbaHexData = BgComm::HexStringToByteArray(qstrData, &ok);// toHex
            qDebug() << "qbaHexData: " << qbaHexData;
            m_pSerialPort->write(qbaHexData);
}

void MainWindow::SlotDCOpenButton()
{
    QString qstrData = "23 23 00 A1 00 00 00 01 00 00 00 00 01 9D 0D 0A";
    bool ok;
    QByteArray qbaHexData = BgComm::HexStringToByteArray(qstrData, &ok);// toHex
    qDebug() << "qbaHexData: " << qbaHexData;
    m_pSerialPort->write(qbaHexData);
}

void MainWindow::SlotDCCloseButton()
{
    QString qstrData = "23 23 00 A1 00 00 00 01 00 00 00 00 00 C3 0D 0A";
    bool ok;
    QByteArray qbaHexData = BgComm::HexStringToByteArray(qstrData, &ok);// toHex
    qDebug() << "qbaHexData: " << qbaHexData;
    m_pSerialPort->write(qbaHexData);
}

void MainWindow::initSerialPort()
{
    m_pSerialPort = new QSerialPort();
    connect(m_pSerialPort, SIGNAL(readyRead()), this, SLOT(SlotReadSerial()));
    //
    m_listSerialPortInfo = QSerialPortInfo::availablePorts();
    if(m_listSerialPortInfo.isEmpty())
    {
        qDebug() << "无串口";
    }
    foreach (QSerialPortInfo info, m_listSerialPortInfo) {
            qDebug() <<"init: " <<  info.portName();
        }

            if(m_listSerialPortInfo.isEmpty())
                return;

            // Example use QSerialPort

            m_pSerialPort->setPort(m_listSerialPortInfo.at(0));
            if (!m_pSerialPort->open(QIODevice::ReadWrite))
            {
                qDebug() << " open error!";
                m_pSerialPort->close();
            }
}
