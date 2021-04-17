/**
 *  @file dbmanager.h
 *  @brief Contains the definition of the Dbmanager Class
 */

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "member.h"

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
     * @return
     */
    QSqlTableModel* createMemberTable();

    /**
     * @brief createSalesTable
     *
     * Creates a table for the sales information if not already created
     * @return
     */
    QSqlTableModel* createSalesTable();

    /**
     * @brief addMember
     *
     * Adds a member to the member table of the database
     */
    void addMember(Member newMember);

    /**
     * @brief removeMember
     *
     * Removes a member from the member table of the database
     */
    void removeMember();

    /**
     * @brief addSale
     *
     * Adds a sale to the sales table of the database
     */
    void addSale();

    /**
     * @brief removeSale
     *
     * Removes a sale from the sales table of the database
     */
    void removeSale();

private:
    /**
     * @brief db
     *
     * The database connection represented by this class
     */
    QSqlDatabase db;
};

#endif // DBMANAGER_H
