#include <QApplication>
#include <QDebug>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    //QGuiApplication app(argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
   // return app.exec();
  //  QString configFile = QApplication::applicationDirPath() + "/config.ini";

}

