#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_lineEdit_returnPressed()
{
    /*validCredentials = true;
    this->setVisible(false);
    */
    //MainWindow::setVisible(true);
}
