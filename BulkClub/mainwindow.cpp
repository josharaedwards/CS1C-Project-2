#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // memberView = this->ui->MemberTableView;
    // memberView->setModel(connection.createMemberTable());

    memberModel = connection.createMemberTable();
    memberView = this->ui->MemberTableView;
    memberProxyModel = new QSortFilterProxyModel(this);
    memberProxyModel->setSourceModel(memberModel);
    memberView->setModel(memberProxyModel);

    /// @brief Allows the user to sort the Member table by column
    memberView->setSortingEnabled(true);
    memberView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    memberView->setSelectionBehavior(QAbstractItemView::SelectRows);
    memberView->setSelectionMode(QAbstractItemView::SingleSelection);
    memberView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    salesView = this->ui->salesTableView;
    salesView->setModel(connection.createSalesTable());

    /// @brief Allows the user to sort the sales table by column
    salesView->setSortingEnabled(true);
    salesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    salesView->setSelectionBehavior(QAbstractItemView::SelectRows);
    salesView->setSelectionMode(QAbstractItemView::NoSelection);
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

/// @brief Filter by membership type Combo box index changed
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    this->memberProxyModel->setFilterKeyColumn(2);
    this->memberProxyModel->setFilterRegularExpression(arg1);
    this->memberView->setModel(memberProxyModel);
}
