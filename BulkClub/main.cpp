//Project Partners:
//Joshara Edwards
//Max Kwatcher
//Johnny Wannamaker
//Sean Hostetter

#include "mainwindow.h"

#include <QApplication>

QString style = "VillainStyle";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString styleName = "styles//" + style + ".qss";       //set style file path
    QFile styleFile(styleName);             // Load an application style
    styleFile.open( QFile::ReadOnly );
    QString style( styleFile.readAll() );    // Apply the loaded stylesheet
    a.setStyleSheet( style );

    MainWindow w;
    w.show();
    return a.exec();
}
