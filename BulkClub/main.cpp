//Project Partners:
//Joshara Edwards
//Max Kwatcher
//Johnny Wannamaker
//Sean Hostetter

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}