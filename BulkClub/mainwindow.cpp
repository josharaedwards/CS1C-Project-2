/**
  *
  *
  */

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

    // memberModel = connection.createMemberTable();
    memberModel = createMemberModel(parent, members);
    memberProxyModel = new QSortFilterProxyModel(this);
    memberProxyModel->setSourceModel(memberModel);
    memberProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    memberProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    stackedMemberFilter = new QSortFilterProxyModel(this);
    stackedMemberFilter->setSourceModel(memberProxyModel);
    stackedMemberFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    stackedMemberFilter->setSortCaseSensitivity(Qt::CaseInsensitive);
    memberView = this->ui->MemberTableView;
    memberView->setModel(stackedMemberFilter);

    /// @brief Formats the column sizes by allowing them to stretch
    memberView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // salesModel = connection.createSalesTable();
    salesModel = createSalesModel(parent, sales);
    salesProxyModel = new QSortFilterProxyModel(this);
    salesProxyModel->setSourceModel(salesModel);
    salesProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    salesProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    salesView = this->ui->salesTableView;
    salesView->setModel(salesProxyModel);

    /// @brief Formats the column sizes by allowing them to stretch
    salesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    inventoryModel = connection.createInventoryTable();
    inventoryProxyModel = new QSortFilterProxyModel(this);
    inventoryProxyModel->setSourceModel(inventoryModel);
    inventoryProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    inventoryView = this->ui->inventoryTableView;
    inventoryView->setModel(inventoryProxyModel);

    /// @brief Formats the column sizes by allowing them to stretch
    inventoryView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
    this->ui->stackedWidget->setCurrentIndex(2);
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
    this->stackedMemberFilter->setFilterRegularExpression("");
}

/// @brief Reset the filters present on the sales table
void MainWindow::on_resetSaleFilterButton_released()
{
    this->salesProxyModel->setFilterRegularExpression("");
}

/// @brief Filter sales by date of sale
void MainWindow::on_saleDateEdit_userDateChanged(const QDate &date)
{
    this->salesProxyModel->setFilterRegularExpression(date.toString("MM/dd/yyyy"));
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

/// @brief Returns the database connection
DbManager MainWindow::getConnection()
{
    return connection;
}

/// @brief Admin button to add a new member
void MainWindow::on_addMemButton_released()
{
    /// @brief Takes the user to the add member page
    this->ui->stackedWidget->setCurrentIndex(1);
}

/// @brief Admin button to delete a member
void MainWindow::on_deleteMemButton_released()
{
    /// @brief Getting the memberID of the selected member
    QModelIndex index = ui->MemberTableView->currentIndex();
    QModelIndex indexID = index.model()->index(index.row(), 1, QModelIndex());
    int memNumIn = index.model()->data(indexID, Qt::DisplayRole).toInt();

    /// @brief Finding the member to delete from their memberID
    bool found = false;
    vector<Member> deleteMem;
    deleteMem.push_back(search(members, memNumIn, found));

    /// @brief Opening the popup to confirm member to delete
    DeleteMemberPopup confirmWindow(deleteMem);
    confirmWindow.exec();

    /// @brief Checking if the user wants to delete the member
    if (confirmWindow.getConfirmDelete())
    {
        deleteMember(members, memNumIn);
        memberModel = createMemberModel(parentWidget(), members);
        memberProxyModel->setSourceModel(memberModel);
        stackedMemberFilter->setSourceModel(memberProxyModel);
        ui->MemberTableView->setModel(stackedMemberFilter);
    }
}

/// @brief button to reset filter for searching inventory table
void MainWindow::on_resetInvFilterButton_released()
{
    this->inventoryProxyModel->setFilterRegularExpression("");
    this->ui->invSearchLineEdit->setText("");
}

/// @brief lineEdit to search inventory by product name
void MainWindow::on_invSearchLineEdit_textChanged(const QString &arg1)
{
    this->inventoryProxyModel->setFilterRegularExpression(arg1);
}

/// @brief Cancel button to add a member, returns to tab view
void MainWindow::on_cancelAddMemButton_released()
{
    /// @brief returns the user to the main view of the app
    this->ui->stackedWidget->setCurrentIndex(0);

    /// @brief Clear all the fields
    on_clearAddMemFormButton_released();
}

/// @brief Confirm button to add a member to the table
void MainWindow::on_confirmAddMemButton_released()
{
    /// @brief Check if all fields have info entered
    if (ui->firstNameLineEdit->hasAcceptableInput() && ui->lastNameLineEdit->hasAcceptableInput() &&
        ui->memberIDLineEdit->hasAcceptableInput())
    {
        Member newMember;

        /// @brief Determines from the combo box if the member is Executive
        if (ui->memberTypeComboBox->currentIndex() == 0)
        {
            newMember = Member(ui->firstNameLineEdit->text() + " " + ui->lastNameLineEdit->text(),
                               ui->startMemDateEdit->date().addYears(1),
                               ui->memberIDLineEdit->text().toInt(),
                               false);
        }
        else
        {
            newMember = Member(ui->firstNameLineEdit->text() + " " + ui->lastNameLineEdit->text(),
                               ui->startMemDateEdit->date().addYears(1),
                               ui->memberIDLineEdit->text().toInt(),
                               true);
        }

        // Make this popup more robust, transfer the question to add a sale to this popup
        // include a table with the information entered, ask if everything is correct
        QMessageBox success;
        success.setWindowTitle("Success");
        success.setWindowModality(Qt::ApplicationModal);
        success.setText("You have successfully registered a new member with the Bulk Club");
        success.exec();
        on_clearAddMemFormButton_released();

        /// @brief Add the member retreived from the form to the member vector
        members.push_back(newMember);
        memberModel = createMemberModel(parentWidget(), members);
        memberProxyModel->setSourceModel(memberModel);
        stackedMemberFilter->setSourceModel(memberProxyModel);
        ui->MemberTableView->setModel(stackedMemberFilter);

        /// @brief Next add the optional sale to the sale vector


        ui->stackedWidget->setCurrentIndex(0);

        /// @brief Then refresh the inventory according to the optional added sale(s)
     }
    else
    {
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setWindowModality(Qt::ApplicationModal);
        error.setText("The new member could not be added.");
        error.setInformativeText("One or more fields are unsatisfactory.");
        error.exec();
    }
}

void MainWindow::on_salesTableView_doubleClicked(const QModelIndex &index)
{
    QModelIndex indexID = index.model()->index(index.row(), 0, QModelIndex());
       QString stringID = index.model()->data(indexID, Qt::DisplayRole).toString();

       indexID = index.model()->index(index.row(), 1, QModelIndex());
       int intID = index.model()->data(indexID, Qt::DisplayRole).toInt();

       //-opening-popup--------------------------------------
       SalesPopup openMember(stringID, intID);
       openMember.setModal(true);
       openMember.exec();
       //----------------------------------------------------

}

/// @brief Clear the add member form
void MainWindow::on_clearAddMemFormButton_released()
{
    ui->firstNameLineEdit->setText("");
    ui->lastNameLineEdit->setText("");
    ui->startMemDateEdit->setDate(QDate(2020, 1, 1));
    ui->memberIDLineEdit->setText("");
    ui->memberTypeComboBox->setCurrentIndex(0);
}
