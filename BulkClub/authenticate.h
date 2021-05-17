/**
 *  @file authenticate.h
 *  @brief Contains the definition of the Authenticate Class
 */

#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

#include <QString>
#include <QtSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
using namespace std;

/**
 *  @enum loginStatus
 *  @brief represents the login state of the user
 */
enum loginStatus { FAILED, MANAGER, ADMIN };

/**
 * @class
 * @brief
 * @details
 */
class Authenticate
{
    QString username;        /// @var username -Qstring holding entered username
    QString password;        /// @var password -Qstring holding entered password
    loginStatus state;       /// @var state -loginStatus enum representing the login state of the user
    QSqlDatabase login_db;   /// @var login_db -QSqltDatabase object holding the connection to the username/password database file
public:
    /**
     * @brief Authenticate class constructor
     * @details populates members of the Authenticate class
     */
    Authenticate();
    /**
     * @brief Authenticate class destructor
     * @details runs when the Authenticate object runs out of scope
     */
    ~Authenticate();
    /**
     * @brief attemp function
     * @details returns the loginStatus by comparing passed in username and password with the database
     * @param QString userIn -passed in username
     * @param QString passIN -passed in password
     */
    loginStatus attempt(QString userIn, QString passIn);
    /**
     * @brief getState Authenticate member function
     * @details returns the login status of the user
     */
    loginStatus getState();
    /**
     * @brief logout Authenticate member function
     * @details sets the loginStatus to FAILED
     */
    void logout();
};

#endif // AUTHENTICATE_H
