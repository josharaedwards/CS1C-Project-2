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

    /// @brief Creates the models for the member table
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

    /// @brief Creates the models for the sales table
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

    // setting up page to add a sale
    refreshProductCompleter(); // creating a product completer for adding a new sale
    ui->quantityLineEdit->setValidator(new QIntValidator(0, 100, parentWidget()));

    // function to refresh the subtotal, tax, and total from the product name
    // if all input is valid, initialize a new sale object, add to the global sale vector,
    // and repopulate the sale models and view from the global sale vector
    //  called anytime the text of product or quantity are changed

    // if the user enters a product name found in the auto completer list of QStrings
    // (case insensitive match), then priceLineEdit,  is read only. must be refreshed when
    // text of productLineEdit or quantityLineEdit , but if the
    // user does not enter a name found on the list, then the
    // then the pr

    this->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshProductCompleter()
{
    /// @brief Creating a list of all products listed in the inventory vector
    QStringList products;
    for (int row = 0; row < inventoryModel->rowCount(); row++)
    {
        products << inventoryModel->data(inventoryModel->index(row, 0)).value<QString>();
    }

    /// @brief Using the list of all products as an auto completer for adding a sale
    QCompleter *productCompleter = new QCompleter(products, this);
    productCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    productCompleter->setCompletionMode(QCompleter::InlineCompletion);
    ui->productLineEdit->setCompleter(productCompleter);
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
    this->ui->stackedWidget->setCurrentIndex(3);
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

        /// @brief Determines from the combo box if the member to add is Executive
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

        vector<Member> addMem;          // adding member to a vector
        addMem.push_back(newMember);

        /// @brief Creating a confirmation popup, retreiving whether to add sale or not
        AddMemberPopup addWindow = AddMemberPopup(addMem);  // passing vector to createMemberModel()
        addWindow.exec();
        on_clearAddMemFormButton_released();

        if (addWindow.getConfirmAdd()) // if user presses "confirm" button (do not add sale)
        {
            /// @brief Add the member retreived from the user form to the global member vector
            members.push_back(newMember);

            // reload the models and view from the updated global member vector
            memberModel = createMemberModel(parentWidget(), members);
            memberProxyModel->setSourceModel(memberModel);
            stackedMemberFilter->setSourceModel(memberProxyModel);
            ui->MemberTableView->setModel(stackedMemberFilter);

            // either confirmAdd and addSale are both true or only confirmAdd is true
            /// @brief Next add the optional sale to the sale vector
            if (addWindow.getAddSale())  // if user preses "add sale" button
            {
                // switch to the form to add a sale page of stackedWidget
                ui->stackedWidget->setCurrentIndex(2);
            }
        }

        // return to the main page of the application
        ui->stackedWidget->setCurrentIndex(0);

        /// @brief Next add the optional sale to the sale vector
        if (addWindow.getAddSale())  // if user preses "add sale" button
        {
            ui->stackedWidget->setCurrentIndex(2);
        }

        /// @brief Then refresh the inventory according to the optional added sale(s)

    }
    else  // the user did not fill in all fields of the add member page with valid input
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

/// @brief Return the user to the main view of the app
void MainWindow::on_cancelAddSaleButton_released()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/// @brief Clear all fields of the add sale page
void MainWindow::on_clearSaleButton_released()
{
    ui->dateOfPurchaseDateEdit->setDate(QDate(4, 1, 2021));
    ui->productLineEdit->setText("");
    ui->quantityLineEdit->setText("");
}
