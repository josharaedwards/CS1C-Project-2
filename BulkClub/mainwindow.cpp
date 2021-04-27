#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    memberModel = connection.createMemberTable();

    memberProxyModel = new QSortFilterProxyModel(this);
    memberProxyModel->setSourceModel(memberModel);
    memberView = this->ui->MemberTableView;
    memberView->setModel(memberProxyModel);

    /// @brief Formats the column sizes by allowing them to stretch
    memberView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    salesModel = connection.createSalesTable();
    salesProxyModel = new QSortFilterProxyModel(this);
    salesProxyModel->setSourceModel(salesModel);
    salesView = this->ui->salesTableView;
    salesView->setModel(salesProxyModel);

    /// @brief Formats the column sizes by allowing them to stretch
    salesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logInPushButton_released()
{
    // temporary implementation
    loginStatus state = logInput.attempt(this->ui->lineEditUserID->text(), this->ui->lineEditPassword->text());
    switch(state){
        case FAILED:
            break;
        case MANAGER:
            this->ui->stackedWidget->setCurrentIndex(0);
            break;
        case ADMIN:
            this->ui->stackedWidget->setCurrentIndex(0);
            break;
    }
}

/// @brief logout button pushed
void MainWindow::on_pushButton_released()
{
    logInput.logout();
    this->ui->lineEditPassword->setText("");
    this->ui->stackedWidget->setCurrentIndex(1);
}

/// @brief clear login input
void MainWindow::on_clearPushButton_released()
{
    this->ui->lineEditUserID->setText("");
    this->ui->lineEditPassword->setText("");
}

/// @brief Filter by membership type
void MainWindow::on_memTypeComboBox_currentTextChanged(const QString &arg1)
{
    this->memberProxyModel->setFilterKeyColumn(2);

    if (arg1 != "Any")
    {
        this->memberProxyModel->setFilterRegularExpression(arg1);
    }
    else
    {
        this->memberProxyModel->setFilterRegularExpression("");
    }
}

/// @brief Filter by membership date of expiration
void MainWindow::on_expDateEdit_dateChanged(const QDate &date)
{
    this->memberProxyModel->setFilterKeyColumn(3);
    this->memberProxyModel->setFilterRegularExpression(date.toString("MM/dd/yyyy"));
}

/// @brief Reset the filters present on the member table
void MainWindow::on_resetMemFilterButton_released()
{
    this->memberProxyModel->setFilterRegularExpression("");
}

/// @brief Reset the filters present on the sales table
void MainWindow::on_resetSaleFilterButton_released()
{
    this->salesProxyModel->setFilterRegularExpression("");
}

/// @brief Filter sales by date of sale
void MainWindow::on_saleDateEdit_userDateChanged(const QDate &date)
{
    this->salesProxyModel->setFilterRegularExpression(date.toString("M/d/yyyy"));
}
