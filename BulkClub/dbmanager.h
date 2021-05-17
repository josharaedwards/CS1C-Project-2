/**
 *  @file dbmanager.h
 *  @brief Contains the definition of the DbManager Class
 */

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <iostream>

#include "member.h"
#include "sale.h"
#include "inventory.h"

/**
 * @class DbManager
 * @brief The Database Manager class
 *
 * Handles interfacing with SQL database and performs queries. Requires an existing SQL database.
 */
class DbManager
{
public:
    /**
     * @brief Constructor for Database Manager class
     *
     * Sets connection with a database and opens it
     */
    DbManager();

    /**
     *  @brief Destructor
     *
     *  Closes the database connection.
     */
    ~DbManager();

    /**
     * @brief createMemberTable
     *
     * Creates a table for the member data if not already created
     * @return Pointer to the member table model
     */
    QSqlTableModel* createMemberTable();

    /**
     * @brief createSalesTable
     *
     * Creates a table for the sales information if not already created
     * @return Pointer to the sales table model
     */
    QSqlTableModel* createSalesTable();

    void deleteFromInventory(QString);
    /**
     * @brief createInventoryTable
     *
     * Creates a table for the inventory information if not already created
     * @return Pointer to the inventory table model
     */
    QSqlTableModel* createInventoryTable();

    /**
     * @brief isInInventory
     *
     * returns true if passed QString is in inventory vec
     */
    bool isInInventory(QString);

    /**
     * @brief findInvIndex
     *
     * returns index in inventory vec based on passed string
     */
    int findInvIndex(QString);

    /**
     * @brief popMemVec
     *
     * Populates a vector of Members from the database
     * @return A vector of Members
     */
    vector<Member> popMemVec();

    /**
     * @brief popSaleVec
     *
     * Populates a vector of Sales from the database
     * @return A vector of Sales
     */
    vector<Sale> popSaleVec();

    /**
     * @brief popInvVec
     *
     * Populates the global vector of Inventory items from the sales vector
     *
     */
    vector<Inventory> popInvVec();

    /**
     * @brief saveMemberTable
     *
     * Deletes all existing data in the member table of the database and inserts the member
     * records held within the global member vector
     */
    void saveMemberTable();

    /**
     * @brief saveSalesTable
     *
     * Deletes all existing data in the sales table of the database and inserts the sales
     * records held within the global sales vector
     */
    void saveSalesTable();

    /**
     * @brief saveInventoryTable
     *
     * Deletes all existing data in the inventory table of the database and inserts the
     * inventory records held within the global inventory vector
     */
    void saveInventoryTable();

private:
    /**
     * @brief db
     *
     * The database connection represented by this class
     */
    QSqlDatabase db;
};

#endif // DBMANAGER_H
