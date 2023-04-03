#include "mainwindow.h"
//#include "settings.h"
#include "ui_mainwindow.h"
//#include "ui_settings.h"
#include <iostream>
#include <QVector>
#include <list>
#include <QString>
#include <QDebug>
#include <errno.h>
#include <string.h>
#include <string>
#include <QtSerialPort/QSerialPort>
#include <qserialport.h>
#include <QSerialPortInfo>
#include <QSettings>
#include <QMessageBox>
#include <QFile>
#include <QApplication>
#include <QAbstractButton>
#include <QTimer>


//QList<QSerialPort *> serial;
QSerialPort *serial1;
QSerialPort *serial2;


QString com = "";
QString com1 = "serial1 not set";
QString com2 = "serial2 not set";
QByteArray cmd("v)");
QByteArray remote = "";
QByteArray gogo = "";
QString reply = "";
QString checkAll1 = "unchecked";
QString checkAll2 = "unchecked";
QString text = "";
QString lineEdit_2;
QString command;


QByteArray remote1 = "!";
QByteArray remote2 = "@";
QByteArray remote3 = "#";
QByteArray remote4 = "$";
QByteArray remote5 = "%";
QByteArray remote6 = "^";
QByteArray remote7 = "&";
QByteArray remote8 = "*";
QByteArray remote9 = "!";
QByteArray remote10 = "@";
QByteArray remote11 = "#";
QByteArray remote12 = "$";
QByteArray remote13 = "%";
QByteArray remote14 = "^";
QByteArray remote15 = "&";
QByteArray remote16 = "*";


QVector<QByteArray> remoteList1(8, "");
QVector<QByteArray> remoteList2(8, "");
QVector<QByteArray> cmdList(2, "");

QVectorIterator<QByteArray> i(remoteList2);
QVectorIterator<QByteArray> x(remoteList1);

QString configFile = QApplication::applicationDirPath() + "/config.ini";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    lineEdit_2(NULL)

{
    ui->setupUi(this);
    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setText("");
    serial1 = new QSerialPort();
    serial2 = new QSerialPort();
    MainWindow::comboBox_1_addItem();
    MainWindow::comboBox_2_addItem();
    QSettings settings("config.ini", QSettings::IniFormat);
    initSerial();

    QString slot1 = settings.value("slot1").toString();
    ui->lineEdit_2->setText(slot1);
    QString slot2 = settings.value("slot2").toString();
    ui->lineEdit_3->setText(slot2);
    QString slot3 = settings.value("slot3").toString();
    ui->lineEdit_4->setText(slot3);
    QString slot4 = settings.value("slot4").toString();
    ui->lineEdit_6->setText(slot4);
    QString slot5 = settings.value("slot5").toString();
    ui->lineEdit_7->setText(slot5);
    QString slot6 = settings.value("slot6").toString();
    ui->lineEdit_8->setText(slot6);
    QString slot7 = settings.value("slot7").toString();
    ui->lineEdit_9->setText(slot7);
    QString slot8 = settings.value("slot8").toString();
    ui->lineEdit_10->setText(slot8);
    QString slot9 = settings.value("slot9").toString();
    ui->lineEdit_11->setText(slot9);
    QString slot10 = settings.value("slot10").toString();
    ui->lineEdit_12->setText(slot10);
    QString slot11 = settings.value("slot11").toString();
    ui->lineEdit_13->setText(slot11);
    QString slot12 = settings.value("slot12").toString();
    ui->lineEdit_14->setText(slot12);
    QString slot13 = settings.value("slot13").toString();
    ui->lineEdit_15->setText(slot13);
    QString slot14 = settings.value("slot14").toString();
    ui->lineEdit_16->setText(slot14);
    QString slot15 = settings.value("slot15").toString();
    ui->lineEdit_19->setText(slot15);
    QString slot16 = settings.value("slot16").toString();
    ui->lineEdit_20->setText(slot16);

    QString defaultCom1 = settings.value("COM1").toString();
    ui->comboBox_1->setCurrentText(defaultCom1);
    //MainWindow::openSerialPort1();

    QString defaultCom2 = settings.value("COM2").toString();
    ui->comboBox_2->setCurrentText(defaultCom2);
    //MainWindow::openSerialPort2();

    com1 = defaultCom1;
    com2 = defaultCom2;




}

MainWindow::~MainWindow()
{
    delete ui;
    serial1->close();
    serial2->close();

}
///////////////////////////////////////////////////////////////////////////////////////////////////
// Add the include statement for `QSerialPortInfo`
#include <QSerialPortInfo>

// Add the `initSerial` function
void MainWindow::initSerial() {
    // Get a list of all available serial ports
    QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();

    // If no serial ports are found, print an error message
    if (serialPortInfos.isEmpty()) {
        qDebug() << "No serial ports found";
    } else {
        // Print the number of serial ports found
        qDebug() << "Number of serial ports:" << serialPortInfos.count();

        // Iterate over each available serial port and print its details
        foreach (const QSerialPortInfo& serialPortInfo, serialPortInfos) {
            qDebug() << "Name:" << serialPortInfo.portName()
                     << "Description:" << serialPortInfo.description()
                     << "Manufacturer:" << serialPortInfo.manufacturer();
        }

        // TODO: Open the serial port and configure its settings
    }
}






void MainWindow::MySerialPort()
{
    serial1 = new class QSerialPort(this);
    openSerialPort1();
    serial2 = new class QSerialPort(this);
    openSerialPort2();
}
void MainWindow::closeSerialPort1()
{
    //qDebug() << "serial 1 close";
    if (serial1->isOpen()){
    serial1->close();
    qDebug() << "Serial Port 1 closed: " << qUtf8Printable(com1);}

}
void MainWindow::closeSerialPort2()
{
    //qDebug() << "serial 2 close";
    if (serial2->isOpen()){
    serial2->close();
    qDebug() << "Serial Port 2 closed: " << qUtf8Printable(com2);}

}
void MainWindow::openSerialPort1()
{
    serial1->setPortName(com1);
       // qDebug() << qUtf8Printable(com1);
    serial1->setBaudRate(QSerialPort::Baud115200);
    serial1->setDataBits(QSerialPort::Data8);
    serial1->setParity(QSerialPort::NoParity);
    serial1->setStopBits(QSerialPort::OneStop);
    serial1->setFlowControl(QSerialPort::NoFlowControl);
    if (serial1->open(QIODevice::ReadWrite))
    {
        qDebug() << "Serial Port 1 open: " << qUtf8Printable(com1);


    }
    else
    {
        //Open error
        qDebug() << "Serial Port 1 not ready";

    }
}
void MainWindow::openSerialPort2()
{
    serial2->setPortName(com2);
        qDebug() << qUtf8Printable(com2);
    serial2->setBaudRate(QSerialPort::Baud115200);
    serial2->setDataBits(QSerialPort::Data8);
    serial2->setParity(QSerialPort::NoParity);
    serial2->setStopBits(QSerialPort::OneStop);
    serial2->setFlowControl(QSerialPort::NoFlowControl);
    if (serial2->open(QIODevice::ReadWrite))
    {
        qDebug() << "Serial Port 2 open: " << qUtf8Printable(com2);


    }
    else
    {
        qDebug() << "Serial Port 2 not ready";

    }

}
/////////////////////////////////////////////////////////////////////////
void MainWindow::writeData(const QByteArray &data)
{
    if (serial1->open(QIODevice::ReadWrite))
        serial1->QIODevice::readAll();
    serial1->write(data);
    qDebug("%s", qUtf8Printable(com1));
    qDebug("%s", qUtf8Printable(command));
    reply = serial1->QIODevice::readAll();
    qDebug("%s", qUtf8Printable(reply));





}
void MainWindow::writeData2(const QByteArray &data)
{
    if (serial2->open(QIODevice::ReadWrite))
       serial2->QIODevice::readAll();
    serial2->write(data);
    qDebug("%s", qUtf8Printable(com2));
    qDebug("%s", qUtf8Printable(command));
    reply = serial2->QIODevice::readAll();
    qDebug("%s", qUtf8Printable(reply));


}

/////////////////////////////////////////////////////////////////////////////////////////////////
///
void MainWindow::sendNumbers()
{
    // Run through remotes 1-8
    foreach (const QByteArray &str, remoteList1){
      remote = str;
 if (remote != ""){
 MainWindow::writeData(remote);

        // See what the remote says

 reply = serial1->QIODevice::readAll();
 qDebug("%s", qUtf8Printable(reply));

        //Send all numbers pressed to 1-8
 foreach (const QByteArray &str, cmdList){
   cmd = str;
 MainWindow::writeData(cmd);}
}}

        // Run through remotes 9-16

    foreach (const QByteArray &str, remoteList2){
        remote = str;
     if (remote != ""){


 MainWindow::writeData2(remote);

        // See what the remote says

 reply = serial2->QIODevice::readAll();
 qDebug("%s", qUtf8Printable(reply));

        //Send all numbers pressed to 9-16

 foreach (const QByteArray &str, cmdList){
   cmd = str;
 MainWindow::writeData2(cmd);

}}
    }
    //cmdList.clear();
}
//////////////////////////////////////////////////////////////////////////
void MainWindow::runCommand()
{
    //MySerialPort();

       foreach (const QByteArray &str, remoteList1){
         remote = str;
    if (remote != ""){
    MainWindow::writeData(remote);
    MainWindow::writeData(cmd);}


    }  //closeSerialPort1();

        foreach (const QByteArray &str, remoteList2){
        remote = str;
    if (remote != ""){
    MainWindow::writeData2(remote);
    MainWindow::writeData2(cmd);}

        }
        cmd = "";
        //closeSerialPort1();
        //closeSerialPort2();
}



void MainWindow::on_pushButton_12_clicked()
{
    cmd = "1";
    cmdList.append("1");
    //MainWindow::runCommand();
}
void MainWindow::on_pushButton_2_clicked()
{
    cmd = "2";
    cmdList.append("2");
    //MainWindow::runCommand();
    }
void MainWindow::on_pushButton_3_clicked()
{
    cmd = "3";
    cmdList.append("3");
    //MainWindow::runCommand();
}
void MainWindow::on_pushButton_4_clicked()
{

    cmd = "4";
    cmdList.append("4");
    //MainWindow::runCommand();
}
void MainWindow::on_pushButton_5_clicked()
{

    cmd = "5";
    cmdList.append("5");
    //MainWindow::runCommand();
}
void MainWindow::on_pushButton_6_clicked()
{

    cmd = "6";
    cmdList.append("6");
    //MainWindow::runCommand();

}
void MainWindow::on_pushButton_7_clicked()
{

    cmd = "7";
    cmdList.append("7");
    //MainWindow::runCommand();
}
void MainWindow::on_pushButton_8_clicked()
{
    cmd = "8";
    cmdList.append("8");
    //MainWindow::runCommand();
}
void MainWindow::on_pushButton_9_clicked()
{
    cmd = "9";
    cmdList.append("9");
    //MainWindow::runCommand();
}
void MainWindow::on_pushButton_10_clicked()
{
    cmd = "g";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_11_clicked()
{
    cmd = "N";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_13_clicked()
{

    cmd = "V";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_14_clicked()
{
    cmd = "T";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_16_clicked()
{

    cmd = "U";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_21_clicked()
{

    cmd = "Y";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_22_clicked()
{

    cmd = "fv";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_23_clicked()
{

    cmd = "F";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_24_clicked()
{

    cmd = "E";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_25_clicked()
{

    cmd = "K";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_28_clicked()
{

    cmd = "W";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_33_clicked()
{

    cmd = "Z";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_38_clicked()
{

    cmd = "I";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_35_clicked()
{

    cmd = "a";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_40_clicked()
{
    cmd = "R";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_30_clicked()
{

    cmd = "P";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_39_clicked()
{

    cmd = "L";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_36_clicked()
{

    cmd = "G";
    MainWindow::runCommand();
}
void MainWindow::on_pushButton_0_clicked()
{

    cmd = "0";
    cmdList.append("0");
    //MainWindow::runCommand();
}
////////////////////////////////////////////////////////////////
void MainWindow::on_checkBox_1_clicked(bool checked)
{

    qDebug("Remote 1");
    if (checked){
       remoteList1.insert(0, remote1);
    qDebug("checked");}
    if (!checked){
        remoteList1.removeOne(remote1);
     qDebug("not checked");}
}
void MainWindow::on_checkBox_2_clicked(bool checked)
{
    qDebug("Remote 2");
    if (checked){
       remoteList1.insert(1, remote2);
    qDebug("checked");}
    if (!checked){
    remoteList1.removeOne(remote2);
     qDebug("not checked");}
}
void MainWindow::on_checkBox_3_clicked(bool checked)
{
    qDebug("Remote 3");
        if (checked){
        remoteList1.insert(2, remote3);
        qDebug("checked");}
        if (!checked){
            remoteList1.removeOne(remote3);
         qDebug("not checked");}

}
void MainWindow::on_checkBox_4_clicked(bool checked)
{


    qDebug("Remote 4");
    if (checked){
    remoteList1.insert(3, remote4);
    qDebug("checked");}
    if (!checked){
        remoteList1.removeOne(remote4);
     qDebug("not checked");}



}
void MainWindow::on_checkBox_5_clicked(bool checked)
{
    qDebug("Remote 5");
    if (checked){
    remoteList1.insert(4, remote5);
    qDebug("checked");}
    if (!checked){
        remoteList1.removeOne(remote5);
     qDebug("not checked");}

}
void MainWindow::on_checkBox_6_clicked(bool checked)
{
    qDebug("Remote 6");
    if (checked){
    remoteList1.insert(5, remote6);
    qDebug("checked");}
    if (!checked){
        remoteList1.removeOne(remote6);
     qDebug("not checked");}

}
void MainWindow::on_checkBox_7_clicked(bool checked)
{
    qDebug("Remote 7");
    if (checked){
    remoteList1.insert(6, remote7);
    qDebug("checked");}
    if (!checked){
        remoteList1.removeOne(remote7);
     qDebug("not checked");}

}
void MainWindow::on_checkBox_10_clicked(bool checked)
{
    qDebug("Remote 8");
    if (checked){
    remoteList1.insert(7, remote8);
    qDebug("checked");}
    if (!checked){
        remoteList1.removeOne(remote8);
     qDebug("not checked");}
}


void MainWindow::on_checkBox_11_clicked(bool checked)
{
    qDebug("Remote 9");
    if (checked){
    remoteList2.insert(0, remote9);
    qDebug("checked");}
    if (!checked){
        remoteList2.removeOne(remote9);
     qDebug("not checked");}
}


void MainWindow::on_checkBox_14_clicked(bool checked)
{
    qDebug("*Remote 10");
    if (checked){
        remoteList2.insert(1, remote10);
    qDebug("checked");}
    if (!checked){
        remoteList2.removeOne(remote10);
     qDebug("not checked");}
    ;
}


void MainWindow::on_checkBox_13_clicked(bool checked)
{
    qDebug("*Remote 11");
    if (checked){
        remoteList2.insert(2, remote11);
    qDebug("checked");}
    if (!checked){
        remoteList2.removeOne(remote11);
     qDebug("not checked");}

}


void MainWindow::on_checkBox_12_clicked(bool checked)
{
    qDebug("*Remote 12");
    if (checked){
        remoteList2.insert(3, remote12);
    qDebug("checked");}
    if (!checked){
        remoteList2.removeOne(remote12);
     qDebug("not checked");}
}


void MainWindow::on_checkBox_9_clicked(bool checked)
{
    qDebug("*Remote 13");
    if (checked){
        remoteList2.insert(4, remote13);
    qDebug("checked");}
    if (!checked){
        remoteList2.removeOne(remote13);
     qDebug("not checked");}
}


void MainWindow::on_checkBox_8_clicked(bool checked)
{
    qDebug("*Remote 14");
    if (checked){
        remoteList2.insert(5, remote14);
    qDebug("checked");}
    if (!checked){
        remoteList2.removeOne(remote14);
     qDebug("not checked");}
}
void MainWindow::on_checkBox_17_clicked(bool checked)
{
    qDebug("Remote 15");
    if (checked){
    remoteList2.insert(6, remote15);
    qDebug("checked");}
    if (!checked){
        remoteList2.removeOne(remote15);
        qDebug("not checked");}
}



void MainWindow::on_checkBox_16_clicked(bool checked)
{
    qDebug("Remote 16");
    if (checked){
        remoteList2.insert(7, remote16);
    qDebug("checked");}
    if (!checked){
        remoteList2.removeOne(remote16);
     qDebug("not checked");}
}


void MainWindow::publicRunCommand()
{
    runCommand(); // call private runCommand function internally
}





void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked){
    cmd = "z";
    MainWindow::runCommand();}
    if (!checked){
        cmd = "x";
    MainWindow::runCommand();}
}


/*
void MainWindow::on_lineEdit_41_textChanged(const QString &arg1)
{
   MainWindow::closeSerialPort1();
    com1 = arg1;
    //qDebug("%s", qUtf8Printable(com));
    MainWindow::openSerialPort1();

}


void MainWindow::on_lineEdit_21_textChanged(const QString &arg1)
{
    MainWindow::closeSerialPort2();
    com2 = arg1;
    //qDebug("%s", qUtf8Printable(com));
    MainWindow::openSerialPort2();
}
*/


void MainWindow::on_pushButton1_clicked()
{
    MainWindow::sendNumbers();
    cmdList.clear();
}


void MainWindow::on_LiveTV_clicked()
{
    cmd = "O";
    MainWindow::runCommand();
}


void MainWindow::on_pushButton_15_clicked()
{

        cmd = "S";
        MainWindow::runCommand();
}


void MainWindow::on_pushButton_41_clicked()
{
    cmd = "X";
    MainWindow::runCommand();
}


void MainWindow::on_pushButton_clicked()
{
    cmd = "v";
    MainWindow::runCommand();
}

void MainWindow::comboBox_1_addItem()
{
    ui->comboBox_1->clear();
    foreach (const QSerialPortInfo &ThisPort, QSerialPortInfo::availablePorts())
    {
    ui->comboBox_1->addItem(ThisPort.portName());


    }
}

void MainWindow::on_comboBox_1_textActivated(const QString &arg1)
{


    MainWindow::closeSerialPort1();
     com1 = arg1;
     //qDebug("%s", qUtf8Printable(com));
     MainWindow::openSerialPort1();
     QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
     defaultCom1 = com1;
     settings->setValue("COM1", defaultCom1);
}

void MainWindow::comboBox_2_addItem()
{
    ui->comboBox_2->clear();
    foreach (const QSerialPortInfo &ThisPort, QSerialPortInfo::availablePorts())
    {
    ui->comboBox_2->addItem(ThisPort.portName());
    }
}
void MainWindow::on_comboBox_2_textActivated(const QString &arg1)
{
    /*foreach (const QSerialPortInfo &ThisPort, QSerialPortInfo::availablePorts())
    {
    ui->comboBox_2->addItem(ThisPort.portName());
    }*/



    MainWindow::closeSerialPort2();
     com2 = arg1;
     //qDebug("%s", qUtf8Printable(com));
     MainWindow::openSerialPort2();
     QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
     //QString str_1 = ui->comboBox_2->currentText();
     defaultCom2 = com2;
     settings->setValue("COM2", defaultCom2);
}


void MainWindow::on_checkBox_15_clicked(bool checked)
{
    if (checked){
        checkAll1 = "checked";
        remoteList1.clear();
        ui->checkBox_1->setChecked(1);
        remoteList1.insert(0, remote1);
        ui->checkBox_2->setChecked(1);
        remoteList1.insert(1, remote2);
        ui->checkBox_3->setChecked(1);
        remoteList1.insert(2, remote3);
        ui->checkBox_4->setChecked(1);
        remoteList1.insert(3, remote4);
        ui->checkBox_5->setChecked(1);
        remoteList1.insert(4, remote5);
        ui->checkBox_6->setChecked(1);
        remoteList1.insert(5, remote6);
        ui->checkBox_7->setChecked(1);
        remoteList1.insert(6, remote7);
        ui->checkBox_10->setChecked(1);
        remoteList1.insert(7, remote8);
}
    if (!checked){
        checkAll1 = "unchecked";
        remoteList1.clear();
        remoteList1.insert(0, "");
        remoteList1.insert(1, "");
        remoteList1.insert(2, "");
        remoteList1.insert(3, "");
        remoteList1.insert(4, "");
        remoteList1.insert(5, "");
        remoteList1.insert(6, "");
        remoteList1.insert(7, "");
        ui->checkBox_1->setChecked(0);
        ui->checkBox_2->setChecked(0);
        ui->checkBox_3->setChecked(0);
        ui->checkBox_4->setChecked(0);
        ui->checkBox_5->setChecked(0);
        ui->checkBox_6->setChecked(0);
        ui->checkBox_7->setChecked(0);
        ui->checkBox_10->setChecked(0);
}

}


void MainWindow::on_checkBox_18_clicked(bool checked)
{
    if (checked){
        checkAll2 = "checked";
               remoteList2.clear();
               ui->checkBox_11->setChecked(1);
               remoteList2.insert(0, remote9);
               ui->checkBox_14->setChecked(1);
               remoteList2.insert(1, remote10);
               ui->checkBox_13->setChecked(1);
               remoteList2.insert(2, remote11);
               ui->checkBox_12->setChecked(1);
               remoteList2.insert(3, remote12);
               ui->checkBox_9->setChecked(1);
               remoteList2.insert(4, remote13);
               ui->checkBox_8->setChecked(1);
               remoteList2.insert(5, remote14);
               ui->checkBox_17->setChecked(1);
               remoteList2.insert(6, remote15);
               ui->checkBox_16->setChecked(1);
               remoteList2.insert(7, remote16);}
    if (!checked){
        checkAll2 = "unchecked";
        remoteList2.clear();
        remoteList2.insert(0, "");
        remoteList2.insert(1, "");
        remoteList2.insert(2, "");
        remoteList2.insert(3, "");
        remoteList2.insert(4, "");
        remoteList2.insert(5, "");
        remoteList2.insert(6, "");
        remoteList2.insert(7, "");
        ui->checkBox_8->setChecked(0);
        ui->checkBox_9->setChecked(0);
        ui->checkBox_11->setChecked(0);
        ui->checkBox_12->setChecked(0);
        ui->checkBox_13->setChecked(0);
        ui->checkBox_14->setChecked(0);
        ui->checkBox_17->setChecked(0);
        ui->checkBox_16->setChecked(0);
        }
}





void MainWindow::on_pushButton42_clicked()
{
    cmd = "Z";
    MainWindow::runCommand();
    cmd = "Z";
    MainWindow::runCommand();
    cmd = "Z";
    MainWindow::runCommand();
    cmd = "h";
    MainWindow::runCommand();
}


void MainWindow::on_pushButton_17_clicked()
{
    MainWindow::comboBox_1_addItem();
    MainWindow::comboBox_2_addItem();
}


void MainWindow::on_pushButton_18_clicked()
{
    cmd = "J";
    MainWindow::runCommand();
}


void MainWindow::on_pushButton_19_clicked()
{
    cmd = "M";
    MainWindow::runCommand();
}


void MainWindow::on_lineEdit_2_textChanged(const QString &slot1)
{
QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
QString str_1 = ui->lineEdit_2->text();
settings->setValue("slot1", slot1);


}


void MainWindow::on_lineEdit_3_textChanged(const QString &slot2)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_3->text();
    settings->setValue("slot2", slot2);
}


void MainWindow::on_lineEdit_4_textChanged(const QString &slot3)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_4->text();
    settings->setValue("slot3", slot3);
}


void MainWindow::on_lineEdit_6_textChanged(const QString &slot4)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_6->text();
    settings->setValue("slot4", slot4);
}


void MainWindow::on_lineEdit_7_textChanged(const QString &slot5)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_7->text();
    settings->setValue("slot5", slot5);
}


void MainWindow::on_lineEdit_8_textChanged(const QString &slot6)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_8->text();
    settings->setValue("slot6", slot6);
}


void MainWindow::on_lineEdit_9_textChanged(const QString &slot7)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_9->text();
    settings->setValue("slot7", slot7);
}

void MainWindow::on_lineEdit_10_textChanged(const QString &slot8)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_10->text();
    settings->setValue("slot8", slot8);
}

void MainWindow::on_lineEdit_11_textChanged(const QString &slot9)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_11->text();
    settings->setValue("slot9", slot9);
}

void MainWindow::on_lineEdit_12_textChanged(const QString &slot10)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_12->text();
    settings->setValue("slot10", slot10);
}

void MainWindow::on_lineEdit_13_textChanged(const QString &slot11)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_13->text();
    settings->setValue("slot11", slot11);
}

void MainWindow::on_lineEdit_14_textChanged(const QString &slot12)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_14->text();
    settings->setValue("slot12", slot12);
}

void MainWindow::on_lineEdit_15_textChanged(const QString &slot13)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_15->text();
    settings->setValue("slot13", slot13);
}

void MainWindow::on_lineEdit_16_textChanged(const QString &slot14)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_16->text();
    settings->setValue("slot14", slot14);
}

void MainWindow::on_lineEdit_19_textChanged(const QString &slot15)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_19->text();
    settings->setValue("slot15", slot15);
}

void MainWindow::on_lineEdit_20_textChanged(const QString &slot16)
{
    QSettings* settings = new QSettings("config.ini", QSettings::IniFormat);
    QString str_1 = ui->lineEdit_20->text();
    settings->setValue("slot16", slot16);
}




void MainWindow::on_pushButton_20_clicked()
{
    cmd = "C";
    MainWindow::runCommand();
}


void MainWindow::on_pushButton_26_clicked()
{
    cmd = "D";
    MainWindow::runCommand();
}


void MainWindow::on_pushButton_27_clicked()
{
    cmd = "H";
    MainWindow::runCommand();
}


void MainWindow::on_pushButton_29_clicked()
{
    cmd = "b";
    MainWindow::runCommand();
}


void MainWindow::on_pushButton_32_clicked()
{
    cmd = "A";
    MainWindow::runCommand();
}


void MainWindow::on_pushButton_31_clicked()
{
    cmd = "B";
    MainWindow::runCommand();
}




