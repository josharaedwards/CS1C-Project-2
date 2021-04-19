#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    /// @brief Create a QTableView to display the member table
    QTableView *memberView = new QTableView;
    memberView->setModel(connection.createMemberTable());

    /// @brief Allows the user to sort the Member table by column
    memberView->setSortingEnabled(true);
    memberView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    memberView->resizeColumnsToContents();
    memberView->show();

    /// @brief Create a QTableView to display the sales table
    QTableView *salesView = new QTableView;
    salesView->setModel(connection.createSalesTable());

    /// @brief Allows the user to sort the sales table by column
    salesView->setSortingEnabled(true);
    salesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    salesView->resizeColumnsToContents();
    salesView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

