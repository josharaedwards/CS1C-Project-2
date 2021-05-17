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

/**
 * @class
 * @brief
 * @details
 */
class memberPopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief
     * @details
     * @param
     * @param
     */
    explicit memberPopup(QString memberID, QWidget *parent = nullptr);
    /**
     * @brief
     * @details
     * @param
     */
    void createMemTable(int index);
    /**
     * @brief
     * @details
     * @param
     */
    void createSaleTable(int index);
    /**
     * @brief
     * @details
     */
    ~memberPopup();

private:
    Ui::memberPopup *ui;    /// @var
};

#endif // MEMBERPOPUP_H
