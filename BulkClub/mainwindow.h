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

#include <QMainWindow>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 *
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_logInPushButton_released();

    void on_pushButton_released();

    void on_clearPushButton_released();

    void on_memTypeComboBox_currentTextChanged(const QString &arg1);

    void on_expDateEdit_dateChanged(const QDate &date);

    void on_resetMemFilterButton_released();

    void on_resetSaleFilterButton_released();

    void on_saleDateEdit_userDateChanged(const QDate &date);

    void on_MemberTableView_doubleClicked(const QModelIndex &index);

    DbManager getConnection();

    void on_addMemButton_released();

    void on_deleteMemButton_released();



    void on_salesTableView_doubleClicked(const QModelIndex &index);

    void on_cancelAddMemButton_released();

    void on_confirmAddMemButton_released();

private:
    Ui::MainWindow *ui;

    QAbstractItemModel *memberModel; /// @var memberModel the source model for the member table
    QAbstractItemModel *salesModel;  /// @var salesModel the source model for the sales table
    QSortFilterProxyModel *memberProxyModel; /// @var memberProxyModel a proxy model for sorting/filtering members
    QSortFilterProxyModel *stackedMemberFilter; /// @var stackedMemberFilter a proxy model for stacking filters on members
    QSortFilterProxyModel *salesProxyModel;  /// @var salesProxyModel a proxy model for sorting/filtering sales
    QTableView *memberView; /// @var memberView the table view where memberProxyModel is shown
    QTableView *salesView;  /// @var salesView the table view where salesProxyModel is shown

    DbManager connection;  /// @var connection DbManager object to retreive data from the database
    Authenticate logInput; /// @var logInput Authenticate object to keep track of user's login status
};
#endif // MAINWINDOW_H
