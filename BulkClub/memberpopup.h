#ifndef MEMBERPOPUP_H
#define MEMBERPOPUP_H

#include "dbmanager.h"
#include "authenticate.h"

#include <QDialog>

#include <QMainWindow>
#include <QTableView>
#include <QtSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class memberPopup;
}

class memberPopup : public QDialog
{
    Q_OBJECT

public:
    explicit memberPopup(QString memberID, QWidget *parent = nullptr);
    ~memberPopup();

private:
    Ui::memberPopup *ui;

    QAbstractItemModel *memberModel; /// @var memberModel the source model for the member table
    QAbstractItemModel *salesModel;  /// @var salesModel the source model for the sales table
    QSortFilterProxyModel *memberProxyModel; /// @var memberProxyModel a proxy model for sorting/filtering members
    QSortFilterProxyModel *salesProxyModel;  /// @var salesProxyModel a proxy model for sorting/filtering sales
    QTableView *memberView; /// @var memberView the table view where memberProxyModel is shown
    QTableView *salesView;  /// @var salesView the table view where salesProxyModel is shown

    DbManager connection;  /// @var connection DbManager object to retreive data from the database
};

#endif // MEMBERPOPUP_H
