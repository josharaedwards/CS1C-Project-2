#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

//global member variable
vector<Member> members;
vector<Sale> sales;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sales = connection.popSaleVec();    //populate sales vector
    members = connection.popMemVec();   //populate members vector
    salesToMembers(members, sales);     //assign sales to each member by ID


    this->setWindowTitle("Not Logged In");

    memberModel = connection.createMemberTable();
    memberProxyModel = new QSortFilterProxyModel(this);
    memberProxyModel->setSourceModel(memberModel);
    stackedMemberFilter = new QSortFilterProxyModel(this);
    stackedMemberFilter->setSourceModel(memberProxyModel);
    memberView = this->ui->MemberTableView;
    memberView->setModel(stackedMemberFilter);

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
    logInput.attempt(this->ui->lineEditUserID->text(), this->ui->lineEditPassword->text());
    switch(logInput.getState())
    {
        case FAILED:
            break;
        case MANAGER:
            this->ui->stackedWidget->setCurrentIndex(0);
            this->ui->addMemButton->setHidden(true);
            this->ui->deleteMemButton->setHidden(true);
            this->setWindowTitle("Manager");
            break;
        case ADMIN:
            this->ui->stackedWidget->setCurrentIndex(0);
            this->ui->addMemButton->setHidden(false);
            this->ui->deleteMemButton->setHidden(false);
            this->setWindowTitle("Administrator");
            break;
    }
}

/// @brief logout button pushed
void MainWindow::on_pushButton_released()
{
    logInput.logout();
    this->ui->lineEditPassword->setText("");
    this->ui->stackedWidget->setCurrentIndex(1);
    this->setWindowTitle("Not Logged In");
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
    this->stackedMemberFilter->setFilterKeyColumn(2);

    if (arg1 != "Any")
    {
        this->stackedMemberFilter->setFilterRegularExpression(arg1);
    }
    else
    {
        this->stackedMemberFilter->setFilterRegularExpression("");
    }
}

/// @brief Filter by membership date of expiration
void MainWindow::on_expDateEdit_dateChanged(const QDate &date)
{
    this->memberProxyModel->setFilterKeyColumn(3);
    this->memberProxyModel->setFilterWildcard(date.toString("MM/*/yyyy"));
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

///@brief double clicking any member should create a popup containing their purchases
void MainWindow::on_MemberTableView_doubleClicked(const QModelIndex &index)
{
    QModelIndex indexID = index.model()->index(index.row(), 1, QModelIndex());
    QString stringID = index.model()->data(indexID, Qt::DisplayRole).toString();

    //-opening-popup--------------------------------------
    memberPopup openMember(stringID);
    openMember.setModal(true);
    openMember.exec();
    //----------------------------------------------------
}

DbManager MainWindow::getConnection(){
    return connection;
}

/// @brief Admin button to add a new member
void MainWindow::on_addMemButton_released()
{

}

/// @brief Admin button to delete a member
void MainWindow::on_deleteMemButton_released()
{

}
