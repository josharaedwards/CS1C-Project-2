#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // create a QTreeView to display the member table
    QTableView *memberView = new QTableView;
    memberView->setModel(connection.createMemberTable());
    memberView->show();

    // create a QTreeView to display the sales table
    QTableView *salesView = new QTableView;
    salesView->setModel(connection.createSalesTable());
    salesView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

