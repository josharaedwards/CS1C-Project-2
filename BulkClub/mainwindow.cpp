#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create a QTreeView to display to the UI of the database
}

MainWindow::~MainWindow()
{
    delete ui;
}

