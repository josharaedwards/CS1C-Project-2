#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /// @brief Create a QTableView to display the member table
    QTableView *memberView; //= new QTableView;
    memberView = this->ui->MemberTableView;
    memberView->setModel(connection.createMemberTable());

    /// @brief Allows the user to sort the Member table by column
    memberView->setSortingEnabled(true);
    memberView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //memberView->resizeColumnsToContents();

    memberView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    memberView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    memberView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    memberView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    /// @brief Create a QTableView to display the sales table
    QTableView *salesView;
    salesView = this->ui->salesTableView;
    salesView->setModel(connection.createSalesTable());

    /// @brief Allows the user to sort the sales table by column
    salesView->setSortingEnabled(true);
    salesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //salesView->resizeColumnsToContents();

    salesView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    salesView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    salesView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    salesView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    salesView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

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
