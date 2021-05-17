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
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadProductCompleter();
    void refreshSalePage();
    void refreshGrandTotal();

private slots:
    /**
     * @brief
     * @details
     */
    void on_logInPushButton_released();
    /**
     * @brief
     * @details
     */
    void on_pushButton_released();
    /**
     * @brief
     * @details
     */
    void on_clearPushButton_released();
    /**
     * @brief
     * @details
     */
    void on_memTypeComboBox_currentTextChanged(const QString &arg1);
    /**
     * @brief
     * @details
     */
    void on_expDateEdit_dateChanged(const QDate &date);
    /**
     * @brief
     * @details
     */
    void on_resetMemFilterButton_released();
    /**
     * @brief
     * @details
     */
    void on_resetSaleFilterButton_released();
    /**
     * @brief
     * @details
     */
    void on_saleDateEdit_userDateChanged(const QDate &date);
    /**
     * @brief
     * @details
     */
    void on_MemberTableView_doubleClicked(const QModelIndex &index);
    /**
     * @brief
     * @details
     */
    DbManager getConnection();
    /**
     * @brief
     * @details
     */
    void on_addMemButton_released();
    /**
     * @brief
     * @details
     */
    void on_deleteMemButton_released();
    /**
     * @brief
     * @details
     */
    void on_resetInvFilterButton_released();
    /**
     * @brief
     * @details
     */
    void on_invSearchLineEdit_textChanged(const QString &arg1);
    /**
     * @brief
     * @details
     */
    void on_cancelAddMemButton_released();
    /**
     * @brief
     * @details
     */
    void on_confirmAddMemButton_released();
    /**
     * @brief
     * @details
     */
    void on_salesTableView_doubleClicked(const QModelIndex &index);
    /**
     * @brief
     * @details
     */
    void on_clearAddMemFormButton_released();
    /**
     * @brief
     * @details
     */
    void on_cancelAddSaleButton_released();
    /**
     * @brief
     * @details
     */
    void on_clearSaleButton_released();
    /**
     * @brief
     * @details
     */
    void on_productLineEdit_textChanged(const QString &arg1);
    /**
     * @brief
     * @details
     */
    void on_confirmAddSaleButton_released();
    /**
     * @brief
     * @details
     */
    void on_quantityLineEdit_textChanged(const QString &arg1);
    /**
     * @brief
     * @details
     */
    void on_memStatusButton_released();
    /**
     * @brief
     * @details
     */
    void on_costColButton_released();
    /**
     * @brief
     * @details
     */
    void on_buttonAddInvItem_released();
    /**
     * @brief
     * @details
     */
    void on_buttonDelInvItem_released();

private:
    Ui::MainWindow *ui;
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
