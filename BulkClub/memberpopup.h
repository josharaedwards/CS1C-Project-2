/**
 *  @file memberpopup.h
 *  @brief Contains the definition of the memberPopup Class
 */

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
    void createMemTable(int index);
    void createSaleTable(int index);
    ~memberPopup();

private:
    Ui::memberPopup *ui;
};

#endif // MEMBERPOPUP_H
