#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
//#include "sshwindow.h"
#include "qlabel.h"
#include <QThread>



class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void publicRunCommand(); // declare public function

private slots:

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_33_clicked();
    void on_pushButton_38_clicked();
    void on_pushButton_35_clicked();
    void on_pushButton_40_clicked();
    void on_pushButton_30_clicked();
    void on_pushButton_39_clicked();
    void on_pushButton_36_clicked();
    void on_pushButton_0_clicked();
    void on_checkBox_17_clicked(bool checked);
    void on_checkBox_1_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_checkBox_3_clicked(bool checked);
    void on_checkBox_4_clicked(bool checked);
    void on_checkBox_5_clicked(bool checked);
    void on_checkBox_6_clicked(bool checked);
    void on_checkBox_7_clicked(bool checked);
    void on_checkBox_10_clicked(bool checked);
    void on_checkBox_11_clicked(bool checked);
    void on_checkBox_14_clicked(bool checked);
    void on_checkBox_13_clicked(bool checked);
    void on_checkBox_12_clicked(bool checked);
    void on_checkBox_9_clicked(bool checked);
    void on_checkBox_8_clicked(bool checked);
    void on_checkBox_16_clicked(bool checked);
    void runCommand();
    void on_checkBox_clicked(bool checked);
    void openSerialPort1();
    void openSerialPort2();
    void writeData(const QByteArray &data);
    void writeData2(const QByteArray &data);
    void MySerialPort();
    void closeSerialPort1();
    void closeSerialPort2();
    void sendNumbers();
    void on_pushButton1_clicked();
    void on_LiveTV_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_41_clicked();
    void on_pushButton_clicked();
    void comboBox_1_addItem();
    void comboBox_2_addItem();
    void on_comboBox_1_textActivated(const QString &arg1);
    void on_comboBox_2_textActivated(const QString &arg1);
    void on_checkBox_15_clicked(bool checked);
    void on_checkBox_18_clicked(bool checked);
    void on_pushButton42_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_3_textChanged(const QString &arg1);
    void on_lineEdit_4_textChanged(const QString &arg1);
    void on_lineEdit_6_textChanged(const QString &arg1);
    void on_lineEdit_7_textChanged(const QString &arg1);
    void on_lineEdit_8_textChanged(const QString &arg1);
    void on_lineEdit_9_textChanged(const QString &arg1);
    void on_lineEdit_10_textChanged(const QString &arg1);
    void on_lineEdit_11_textChanged(const QString &arg1);
    void on_lineEdit_12_textChanged(const QString &arg1);
    void on_lineEdit_13_textChanged(const QString &arg1);
    void on_lineEdit_14_textChanged(const QString &arg1);
    void on_lineEdit_15_textChanged(const QString &arg1);
    void on_lineEdit_16_textChanged(const QString &arg1);
    void on_lineEdit_19_textChanged(const QString &arg1);
    void on_lineEdit_20_textChanged(const QString &arg1);
    //void on_checkBox_18_clicked();
    //void on_checkBox_15_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_27_clicked();
    void on_pushButton_29_clicked();
    void on_pushButton_32_clicked();
    void on_pushButton_31_clicked();
    void on_serialOuput_textChanged();

    void on_serialOuput_windowIconTextChanged(const QString &iconText);

private:
    Ui::MainWindow *ui;
    //sshwindow sshwindowObj;
    QLabel* lineEdit_2;
    QString slot1;
    QString slot2;
    QString slot3;
    QString slot4;
    QString slot5;
    QString slot6;
    QString slot7;
    QString slot8;
    QString slot9;
    QString slot10;
    QString slot11;
    QString slot12;
    QString slot13;
    QString slot14;
    QString slot15;
    QString slot16;
    QString defaultCom1;
    QString defaultCom2;


};
#endif // MAINWINDOW_H
