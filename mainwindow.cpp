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
    initSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotReadSerial()
{
    QByteArray qa = m_pSerialPort->readAll();
    qDebug() << "size: " << qa.size() << qa;
}

void MainWindow::SlotCheckButton()
{
            QString qstrData = "23 23 00 A7 00 00 00 00 00 00 00 00 2F 0D 0A";
            bool ok;
            QByteArray qbaHexData = BgComm::HexStringToByteArray(qstrData, &ok);
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
