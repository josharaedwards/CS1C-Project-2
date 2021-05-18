/**
  * @file mainwindow.cpp
  *
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "splashscreen.h"

#include <iostream>
#include <QMovie>

// global variables
vector<Member> members;
vector<Sale> sales;
vector<Inventory> inventory;

/**
 * @brief MainWindow::MainWindow
 *
 * Default construstor of the MainWindow class
 * @param parent The parent widget
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    splashScreen splash;
    splash.setModal(true);
    splash.exec();

    ui->setupUi(this);

    //--logos-and-gifs------------------------------------------------------------------------------------------------
    this->ui->BulkClubLogo->setPixmap(QPixmap("icons//BulkClub Pro™.png").scaled(QSize(300, 60), Qt::KeepAspectRatio));
    this->ui->BulkClubProLabel->setPixmap(QPixmap("icons//BulkClub Pro™.png").scaled(QSize(300, 60), Qt::KeepAspectRatio));

    QLabel label;
    QMovie *movie = new QMovie("icons//VillainconValley_LoadingT.gif");
    movie->setScaledSize(QSize(220, 135));

    this->ui->logoLabel->setMovie(movie);
    movie->start();

    /// @brief Creating icons for the tabs
    QIcon memIcon("icons//user.png");       //CREATE TAB ICONS
    QIcon salesIcon("icons//money.png");
    QIcon invIcon("icons//boxes.png");
    QIcon villIcon("icons//villainIcon.png");
    ui->tabWidget->setTabIcon(0, memIcon);  //SETTING TAB ICONS
    ui->tabWidget->setTabIcon(1, salesIcon);
    ui->tabWidget->setTabIcon(2, invIcon);
    ui->tabWidget->setIconSize(QSize(20, 20));
    ui->pushButton_2->setIcon(villIcon);
    ui->pushButton_2->setIconSize(QSize(30, 30));
    //----------------------------------------------------------------------------------------------------------------

    sales = connection.popSaleVec();    //populate sales vector
    members = connection.popMemVec();   //populate members vector
    salesToMembers(members, sales);     //assign sales to each member by ID
    inventory = connection.popInvVec(); //populate inventory vector

    // for testing purposes
    int vecSize = inventory.size();
    for(int i = 0; i < vecSize; i++)
    {
        cout << "inventory[" << i << "]: " << inventory[i].getName().toStdString() << " " << inventory[i].getPrice()
             << " " << inventory[i].getQuantity() << " " << inventory[i].getTotal() << endl;
    }

    /// @brief Defaults the winodw title to Not Logged In
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

    /// @brief Hide the cost to renew column at first
    memberView->setColumnHidden(4, true);


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

    /// @brief creates the models for the inventory table from the .sqlite
    inventoryModel = connection.createInventoryTable();
    inventoryProxyModel = new QSortFilterProxyModel(this);
    inventoryProxyModel->setSourceModel(inventoryModel);
    inventoryProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    inventoryProxyModel->setFilterKeyColumn(0);
    inventoryProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    inventoryProxyModel->sort(0, Qt::AscendingOrder);
    inventoryView = this->ui->inventoryTableView;
    inventoryView->setModel(inventoryProxyModel);

    ///@brief calculates the total spent from the inventory vector and updates the appropriate label
    refreshGrandTotal();

    /// @brief Formats the column sizes by allowing them to stretch
    inventoryView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /// @brief Creates a validator for the member ID of a new member, only integers accepted
    ui->memberIDLineEdit->setValidator(new QIntValidator(10000, 99999, parent));

    /// @brief Creating an auto completer for adding a product to a new sale
    loadProductCompleter();
    ui->productLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[a-z-A-Z-0-9-.-/ ]+")));

    /// @brief Creates a validator for the Quantity of a new sale, only integers accepted
    ui->quantityLineEdit->setValidator(new QIntValidator(0, 999, parent));

    this->setVisible(false);
}

/// @brief Destructor of the MainWindow Class
MainWindow::~MainWindow()
{
    delete ui;
}

/// @brief Initializes the unique list of products from the current state of the inventory model
void MainWindow::loadProductCompleter()
{
    // clear the list before adding again
    products.clear();

    /// @brief Creating a list of all products listed in the inventory model
    for (int row = 0; row < inventoryModel->rowCount(); row++)
    {
        products << inventoryModel->data(inventoryModel->index(row, 0)).value<QString>();
    }

    /// @brief Using the list of all products as an auto completer for adding a sale
    QCompleter *productCompleter = new QCompleter(products, this);
    productCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    productCompleter->setCompletionMode(QCompleter::PopupCompletion);
    productCompleter->setFilterMode(Qt::MatchContains);
    ui->productLineEdit->setCompleter(productCompleter);
    ui->lineEditDel->setCompleter(productCompleter);
}

/// @brief Refreshes the unit price, subtotal, tax, and total from the quantity and product name
void MainWindow::refreshSalePage()
{
    double unitPrice = 0.00;
    double quantity = 0.00;
    double subtotal = 0.00;
    double tax = 0.00;
    double total = 0.00;

    // iterating through the inventory model, retrieving the unit price
    for (int row = 0; row < inventoryModel->rowCount(); row++)
    {
        QString saleProduct = inventoryModel->data(inventoryModel->index(row, 0)).value<QString>();

        if (ui->productLineEdit->text() == saleProduct)
        {
            unitPrice = inventoryModel->data(inventoryModel->index(row, 1)).value<double>();
            quantity = ui->quantityLineEdit->text().toDouble();
            subtotal = unitPrice * quantity;
            tax = subtotal * 0.0775;
            total = subtotal + tax;
        }

        ui->unitPriceLineEdit->setText(QString::number(unitPrice, 'f', 2));
        ui->subtotalLineEdit->setText(QString::number(subtotal, 'f', 2));
        ui->taxLineEdit->setText(QString::number(tax, 'f', 2));
        ui->totalLineEdit->setText(QString::number(total, 'f', 2));
    }
}

/// @brief Calculates the grand total (including tax) of every item sold
void MainWindow::refreshGrandTotal()
{
    ///@brief calculates the total spent from the inventory vector and updates the appropriate label
    int invVecSize = inventory.size();
    double invGrandTotal = 0;
    for(int i = 0; i < invVecSize; i++)
    {
        invGrandTotal += inventory[i].getTotal();
    }
    invGrandTotal += invGrandTotal * 0.0775;
    ui->labelCalculatedGrandTotal->setText("$" + QString::number(invGrandTotal));
    ui->labelCalculatedGrandTotal->setStyleSheet("QLabel { color : black; }");
}

/// @brief Hiding or revealing features based on log in status
void MainWindow::on_logInPushButton_released()
{
    logInput.attempt(ui->lineEditUserID->text(), ui->lineEditPassword->text());
    switch(logInput.getState())
    {
        case FAILED:
            break;
        case MANAGER:
            ui->stackedWidget->setCurrentIndex(0);
            ui->addMemButton->setHidden(true);
            ui->deleteMemButton->setHidden(true);
            ui->buttonAddInvItem->setHidden(true);
            ui->buttonDelInvItem->setHidden(true);
            ui->lineEditDel->setHidden(true);
            ui->addSaleButton->setHidden(true);
            setWindowTitle("Manager");
            break;
        case ADMIN:
            ui->stackedWidget->setCurrentIndex(0);
            ui->addMemButton->setHidden(false);
            ui->deleteMemButton->setHidden(false);
            ui->buttonAddInvItem->setHidden(false);
            ui->buttonDelInvItem->setHidden(false);
            ui->lineEditDel->setHidden(false);
            ui->addSaleButton->setHidden(false);
            setWindowTitle("Administrator");
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
        // removing the member from the global member vector
        deleteMember(members, memNumIn);

        // reloading the models and view with the updated member vector
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

    QString tempQString;
    string tempString;
    double tempDouble;
    int rowCount = inventoryProxyModel->rowCount();
    double newTotal = 0;

    for(int i = 0; i < rowCount; i++)
    {
        // retrieves data from current row, last column
        tempQString = inventoryProxyModel->data(inventoryProxyModel->index(i, 3)).toString();
        tempDouble = tempQString.toDouble();
        newTotal += tempDouble;
    }
    // applies sales tax to the total
    newTotal += newTotal * 0.0775;
    this->ui->labelCalculatedGrandTotal->setText("$" + QString::number(newTotal, 'f', 2));
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
        Member newMember;     // a new Member object to be added to the global member vector

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

        vector<Member> addMem;          // adding the member to a vector for display purposes
        addMem.push_back(newMember);

        /// @brief Creating a confirmation popup, retreiving whether to add sale or not
        AddMemberPopup addWindow(addMem);  // passing vector of member to createMemberModel()

        addWindow.exec();

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
                // switch to the page of stackedWidget with the form to add a sale
                ui->stackedWidget->setCurrentIndex(2);
                ui->nameLineEdit->setText(newMember.getName());
                ui->memIDLineEdit->setText(QString::number(newMember.getMemNum()));
            }
            else
            {
                // return to the main page of the application
                ui->stackedWidget->setCurrentIndex(0);
            }
        }

        on_clearAddMemFormButton_released(); // clear the form
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

/// @brief Triggered when the sales table is double clicked, opens a detailed sales report
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
    on_clearSaleButton_released();
}

/// @brief Clear all fields of the add sale page
void MainWindow::on_clearSaleButton_released()
{
    ui->dateOfPurchaseDateEdit->setDate(QDate(2021, 4, 1));
    ui->productLineEdit->setText("");
    ui->quantityLineEdit->setText("");
    ui->unitPriceLineEdit->setText("");
    ui->subtotalLineEdit->setText("");
    ui->taxLineEdit->setText("");
    ui->totalLineEdit->setText("");
}

/// @brief The text of the product name of the new sale has changed
void MainWindow::on_productLineEdit_textChanged(const QString &arg1)
{
    refreshSalePage();
}

/// @brief The confirm button to add a new sale was pressed
void MainWindow::on_confirmAddSaleButton_released()
{
    // if all user input is valid
    if (ui->productLineEdit->hasAcceptableInput() && ui->quantityLineEdit->hasAcceptableInput() &&
        ui->unitPriceLineEdit->text().toDouble() != 0)
    {
        // initialize a new sale object
        Sale newSale;

        newSale.setName(ui->productLineEdit->text());
        newSale.setDate(ui->dateOfPurchaseDateEdit->date());
        newSale.setMemNum(ui->memIDLineEdit->text().toInt());
        newSale.setPrice(ui->unitPriceLineEdit->text().toDouble());
        newSale.setQuantity(ui->quantityLineEdit->text().toInt());

        // initializing a popup to confirm the sales to be added
        AddSalePopup addSaleWindow(newSale);
        addSaleWindow.exec();

        // user confirms they want to add all of the purchases in the addSales vector
        if (addSaleWindow.getConfirmSales())
        {
            // add to the global sale vector
            sales.insert(sales.end(), AddSalePopup::addSales.begin(), AddSalePopup::addSales.end());

            // add to the member instance vector
            salesToMembers(members, sales);

            // repopulate the sale models and view with the updated global sale vector
            salesModel = createSalesModel(parentWidget(), sales);
            salesProxyModel->setSourceModel(salesModel);
            salesView->setModel(salesProxyModel);

            // update the global inventory vector
            DbManager d;
            d.addSalesToInv(AddSalePopup::addSales);
            d.saveInventoryTable();
            inventoryModel = connection.createInventoryTable();
            inventoryProxyModel->setSourceModel(inventoryModel);
            inventoryView->setModel(inventoryProxyModel);

            // update the grand total
            refreshGrandTotal();

            AddSalePopup::addSales.clear();

            // return to the main page of the application
            ui->stackedWidget->setCurrentIndex(0);
        }
        else if (!addSaleWindow.getAnotherSale())
        {
            AddSalePopup::addSales.pop_back();
        }

        // clear the add sale page
        on_clearSaleButton_released();
    }
    else
    {
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setWindowModality(Qt::ApplicationModal);
        error.setText("The new sale could not be added.");
        error.setInformativeText("One or more fields are unsatisfactory.");
        error.exec();
    }
}

/// @brief The text for quantity of a new sale was changed
void MainWindow::on_quantityLineEdit_textChanged(const QString &arg1)
{
    // refresh the subtotal from the product name and quantity
    refreshSalePage();
}

void MainWindow::on_memStatusButton_released()
{
    MemberTypePopup openMember(logInput.getState());
    openMember.setModal(true);
    openMember.exec();
}

/// @brief When the hide/unhide cost to renew button is pressed
void MainWindow::on_costColButton_released()
{
    if (memberView->isColumnHidden(4))
    {
        memberView->setColumnHidden(4, false);
        ui->costColButton->setText("Hide Cost");
    }
    else
    {
        memberView->setColumnHidden(4, true);
        ui->costColButton->setText("Show Cost");
    }
}

/// @brief Triggered when user presses the button to add an inventory item
void MainWindow::on_buttonAddInvItem_released()
{
    Inventory newItem;
    AddInvPopup newPopup(newItem);
    newPopup.setModal(true);
    newPopup.exec();

    if(newPopup.Accepted)
    {
        inventoryModel = connection.createInventoryTable();
        inventoryProxyModel->setSourceModel(inventoryModel);
        inventoryView->setModel(inventoryProxyModel);

        refreshGrandTotal();
    }
    loadProductCompleter();
}

/// @brief Triggered when the user presses the button to delete an inventory item
void MainWindow::on_buttonDelInvItem_released()
{
    QString tempName;
    DbManager d;
    int tempIndex;
    tempName = ui->lineEditDel->text();
    if(tempName != "")
    {
        tempIndex = d.findInvIndex(tempName);

        inventory.erase(inventory.begin() + tempIndex);
        d.saveInventoryTable();

        inventoryModel = connection.createInventoryTable();
        inventoryProxyModel->setSourceModel(inventoryModel);
        inventoryView->setModel(inventoryProxyModel);

        refreshGrandTotal();
        ui->lineEditDel->setText("");
    }
    loadProductCompleter();
}

/// @brief Triggered when the user presses the button to add a sale to a specific user
void MainWindow::on_addSaleButton_released()
{
    // switching over to the page of the widget with the form to add a sale
    ui->stackedWidget->setCurrentIndex(2);

    /// @brief Getting the memberID of the selected member
    QModelIndex index = ui->MemberTableView->currentIndex();
    QModelIndex indexID = index.model()->index(index.row(), 1, QModelIndex());
    int memNum = index.model()->data(indexID, Qt::DisplayRole).toInt();

    // retrieving the member from the members vector
    bool found = false;
    Member addSaleMember = search(members, memNum, found);

    // setting the text of the read only fields
    ui->nameLineEdit->setText(addSaleMember.getName());
    ui->memIDLineEdit->setText(QString::number(addSaleMember.getMemNum()));
}
