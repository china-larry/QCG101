#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void SlotReadSerial();
private slots:
    void SlotCheckButton();
private:
    void initSerialPort();
private:
    Ui::MainWindow *ui;
    QPushButton *m_pFlagPushButton;
    QSerialPort *m_pSerialPort;
    QList<QSerialPortInfo> m_listSerialPortInfo;
};

#endif // MAINWINDOW_H
