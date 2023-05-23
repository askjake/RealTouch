#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <iostream>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}






MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClick(QString buttonName)
{
    // Call sgs_remote.py with positional arguments
    QProcess *process = new QProcess(this);
    // QProcess process;
    qDebug() << "clicking: " << qUtf8Printable(buttonName);

    // Connect to the finished() signal of the QProcess object
    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));


    // Start the process and pass the arguments
    process->start("python", QStringList() << "sgs_remote.py" << "-n" << "stb3" << buttonName);


    // process.waitForFinished();
 }

void MainWindow::clicked_home()
{
    QString buttonName = "Home";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_one_clicked()
{
    QString buttonName = "1";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_two_clicked()
{
    QString buttonName = "2";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_three_clicked()
{
    QString buttonName = "3";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_four_clicked()
{
    QString buttonName = "Four";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_five_clicked()
{
    QString buttonName = "5";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_six_clicked()
{
    QString buttonName = "6";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_seven_clicked()
{
    QString buttonName = "7";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_eight_clicked()
{
    QString buttonName = "8";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_nine_clicked()
{
    QString buttonName = "9";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_diamond_clicked()
{
    QString buttonName = "Diamond";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_zero_clicked()
{
    QString buttonName = "0";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_ddiamond_clicked()
{
    QString buttonName = "DoubleDiamond";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_vodown_clicked()
{
    QString buttonName = "Volume Down";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_volup_clicked()
{
    QString buttonName = "Volume Up";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_mute_clicked()
{
    QString buttonName = "Mute";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_recall_clicked()
{
    QString buttonName = "Recall";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_chdown_clicked()
{
    QString buttonName = "Channel Down";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_chup_clicked()
{
    QString buttonName = "Channel Up";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_rwd_pressed()
{
    QString buttonName = "RWD";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_rwd_released()
{
    // Handle the released event for RWD button
    // You can add your logic here
}

void MainWindow::on_ffd_pressed()
{
    QString buttonName = "FFD";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_ffd_released()
{
    // Handle the released event for FFD button
    // You can add your logic here
}

void MainWindow::on_play_clicked()
{
    QString buttonName = "Play";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_back_clicked()
{
    QString buttonName = "Back";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_info_clicked()
{
    QString buttonName = "Info";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}


void MainWindow::on_down_clicked()
{
    QString buttonName = "Down";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_left_clicked()
{
    QString buttonName = "Left";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_right_clicked()
{
    QString buttonName = "Right";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_select_clicked()
{
    QString buttonName = "Select";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_options_clicked()
{
    QString buttonName = "Options";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_up_clicked()
{
    QString buttonName = "Up";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_voice_clicked()
{
    QString buttonName = "Voice";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_dvr_clicked()
{
    QString buttonName = "DVR";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}

void MainWindow::on_guide_clicked()
{
    QString buttonName = "Guide";
    buttonClick(buttonName); // Call a function with buttonName as an argument
}


