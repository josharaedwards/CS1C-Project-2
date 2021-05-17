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
 * @class memberPopup
 * @brief class representing the MemberPopup window
 * @details shows information relating to a member, as well as their sales information and a receipt
 */
class memberPopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief memberPopup overloaded constructor
     * @details constructs the memebrPopup window with passed in information
     * @param QString memberID -passed in memberID to populated a table with said Member's info
     */
    explicit memberPopup(QString memberID, QWidget *parent = nullptr);
    /**
     * @brief createMemTable function
     * @details function that populates the member information table
     * @param index representing which member in Member vector to display
     */
    void createMemTable(int index);
    /**
     * @brief createSaleTable function
     * @details function that populates a table with all the Member's sales info
     * @param index to find the Member containing said sales info
     */
    void createSaleTable(int index);
    /**
     * @brief memberPopup destructor
     * @details closes the MemberPopup window
     */
    ~memberPopup();

private:
    Ui::memberPopup *ui;    /// @var pointer representing the ui for the windo
};

#endif // MEMBERPOPUP_H
