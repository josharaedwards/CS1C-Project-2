//Project Partners:
//Joshara Edwards
//Max Kwatcher
//Johnny Wannamaker
//Sean Hostetter

#include "mainwindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //login l;
    w.show();
    //l.show();
    return a.exec();
}
