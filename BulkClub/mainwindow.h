/**
 *  @file mainwindow.h
 *  @brief Contains the definition of the MainWindow Class
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbmanager.h"
#include "authenticate.h"
#include "helperLib.h"
#include "member.h"
#include "sale.h"
#include "inventory.h"
#include "memberpopup.h"
#include "salespopup.h"
#include "deletememberpopup.h"
#include "addmemberpopup.h"
#include "addsalepopup.h"
#include "membertypepopup.h"
#include "addinvpopup.h"
#include <vector>

#include <QMainWindow>
#include <QTableView>
#include <QMessageBox>
#include <QCompleter>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The MainWindow class
 * @details An application suitable for Store Manager/Administrator use at the Bulk Club
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @details Default constructor of the MainWindow class
     * @param parent The parent widget
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief ~MainWindow
     * @details The default destructor of the MainWindow class
     */
    ~MainWindow();

    /**
     * @brief loadProductCompleter
     * @details Creates a unique list of products from the inventory model
     */
    void loadProductCompleter();

    /**
     * @brief refreshSalePage
     * @details Calculates the unit price, subtotal, tax, and total from the quantity and product name entered by user
     */
    void refreshSalePage();

    /**
     * @brief refreshGrandTotal
     * @details Calculates the grand total (including tax) of every item sold
     */
    void refreshGrandTotal();

private slots:
    /**
     * @brief on_logInPushButton_released
     * @details Hides or reveals features based on log in status--Admin or Manager
     */
    void on_logInPushButton_released();

    /**
     * @brief on_pushButton_released
     * @details The logout button was pushed and the user retruns to the login page
     */
    void on_pushButton_released();

    /**
     * @brief on_clearPushButton_released
     * @details The text fields of the login page are cleared
     */
    void on_clearPushButton_released();

    /**
     * @brief on_memTypeComboBox_currentTextChanged
     * @details Filters the member table by membership type--Executive, Regular, or Any
     * @param arg1 Choices of the Member Type Combo Box
     */
    void on_memTypeComboBox_currentTextChanged(const QString &arg1);

    /**
     * @brief on_expDateEdit_dateChanged
     * @details Filters the member table by month of membership expiration
     * @param date The date chosen by the user
     */
    void on_expDateEdit_dateChanged(const QDate &date);

    /**
     * @brief on_resetMemFilterButton_released
     * @details Resets all filters present on the member table
     */
    void on_resetMemFilterButton_released();

    /**
     * @brief on_resetSaleFilterButton_released
     * @details Resets all filters present on the sales table
     */
    void on_resetSaleFilterButton_released();

    /**
     * @brief on_saleDateEdit_userDateChanged
     * @details Filters the sales table by date of transaction
     * @param date The date of sale chosen by the user
     */
    void on_saleDateEdit_userDateChanged(const QDate &date);

    /**
     * @brief on_MemberTableView_doubleClicked
     * @details Double clicking any member should produce a popup of all their purchases
     * @param index The index of the table that was double clicked on by the user
     */
    void on_MemberTableView_doubleClicked(const QModelIndex &index);

    /**
     * @brief getConnection
     * @details Returns the database conenction
     * @return DbManager object
     */
    DbManager getConnection();

    /**
     * @brief on_addMemButton_released
     * @details An administrator pressed the button to add a new member
     */
    void on_addMemButton_released();

    /**
     * @brief on_deleteMemButton_released
     * @details An administrator pressed the button to delete a member
     */
    void on_deleteMemButton_released();

    /**
     * @brief on_resetInvFilterButton_released
     * @details Resets all filters present on the inventory table
     */
    void on_resetInvFilterButton_released();

    /**
     * @brief on_invSearchLineEdit_textChanged
     * @details Filters the inventory by product name
     * @param arg1 The name of the item being searched for by the user
     */
    void on_invSearchLineEdit_textChanged(const QString &arg1);

    /**
     * @brief on_cancelAddMemButton_released
     * @details The user cancelled adding a new member and are returned to the main view of the app
     */
    void on_cancelAddMemButton_released();

    /**
     * @brief on_confirmAddMemButton_released
     * @details The user pressed confiorm to adding a new member to the Bulk Club
     */
    void on_confirmAddMemButton_released();

    /**
     * @brief on_salesTableView_doubleClicked
     * @param index Index of the sales model to find the sales report of the same day
     */
    void on_salesTableView_doubleClicked(const QModelIndex &index);

    /**
     * @brief on_clearAddMemFormButton_released
     * @details Clears all text fields of the form to add a new member
     */
    void on_clearAddMemFormButton_released();

    /**
     * @brief on_cancelAddSaleButton_released
     * @details The user indicates they do not want to add any sales to the new member, returned to the main page
     */
    void on_cancelAddSaleButton_released();

    /**
     * @brief on_clearSaleButton_released
     * @details The button to clear all text fields of the add sale page has pressed
     */
    void on_clearSaleButton_released();

    /**
     * @brief on_productLineEdit_textChanged
     * @details The line edit for the product of the new sale to be added to a new member was edited
     * @param arg1 The product being added for a new sale
     */
    void on_productLineEdit_textChanged(const QString &arg1);

    /**
     * @brief on_confirmAddSaleButton_released
     * @details User confirmed they would like to add the sale, a new popup shows all purchases to confirm
     */
    void on_confirmAddSaleButton_released();

    /**
     * @brief on_quantityLineEdit_textChanged
     * @details The line edit for the quantity of a product for a new sale was changed
     * @param arg1 The quantity of the product for a new sale was changed
     */
    void on_quantityLineEdit_textChanged(const QString &arg1);

    /**
     * @brief on_memStatusButton_released
     * @details The button to check how many members should demote/promote their status was pressed
     */
    void on_memStatusButton_released();

    /**
     * @brief on_costColButton_released
     * @details The button to hide/show the cost of a member to renew was pressed
     */
    void on_costColButton_released();

    /**
     * @brief on_buttonAddInvItem_released
     * @details The Admin button to add an item to inventory was pressed
     */
    void on_buttonAddInvItem_released();

    /**
     * @brief on_buttonDelInvItem_released
     * @details The Admin button to delete an item from inventory was pressed
     */
    void on_buttonDelInvItem_released();

    /**
     * @brief on_addSaleButton_released
     * @details An Admin button that allows the user to add a sale to the selected member
     */
    void on_addSaleButton_released();

private:
    Ui::MainWindow *ui; /// @var ui The user interface with the app
    QAbstractItemModel *memberModel; /// @var memberModel the source model for the member table
    QAbstractItemModel *salesModel;  /// @var salesModel the source model for the sales table
    QAbstractItemModel *inventoryModel;  /// @var inventoryModel the source model for the inventory table
    QSortFilterProxyModel *memberProxyModel; /// @var memberProxyModel a proxy model for sorting/filtering members
    QSortFilterProxyModel *stackedMemberFilter; /// @var stackedMemberFilter a proxy model for stacking filters on members
    QSortFilterProxyModel *salesProxyModel;  /// @var salesProxyModel a proxy model for sorting/filtering sales
    QSortFilterProxyModel *inventoryProxyModel;  /// @var inventoryProxyModel a proxy model for sorting/filtering inventory
    QTableView *memberView; /// @var memberView the table view where memberProxyModel is shown
    QTableView *salesView;  /// @var salesView the table view where salesProxyModel is shown
    QTableView *inventoryView;  /// @var inventoryView the table view where inventoryProxyModel is shown

    DbManager connection;  /// @var connection DbManager object to retreive data from the database
    Authenticate logInput; /// @var logInput Authenticate object to keep track of user's login status
    QStringList products; /// @var products A QStringList of all the products offered by the Bulk Club
};
#endif // MAINWINDOW_H
