#include "splashscreen.h"
#include "ui_splashscreen.h"
#include <QMovie>

splashScreen::splashScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::splashScreen)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    QLabel label;
    QMovie *movie = new QMovie("icons//villainSplash.gif");
    movie->setScaledSize(QSize(960, 540));

    this->ui->label->setMovie(movie);
    movie->start();
}

splashScreen::~splashScreen()
{
    delete ui;
}
