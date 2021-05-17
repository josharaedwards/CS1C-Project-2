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
    QString username;        /// @var
    QString password;        /// @var
    loginStatus state;       /// @var
    QSqlDatabase login_db;   /// @var
public:
    /**
     * @brief
     * @details
     */
    Authenticate();
    /**
     * @brief
     * @details
     */
    ~Authenticate();
    /**
     * @brief
     * @details
     * @param
     * @param
     */
    loginStatus attempt(QString userIn, QString passIn);
    /**
     * @brief
     * @details
     */
    loginStatus getState();
    /**
     * @brief
     * @details
     */
    void logout();
};

#endif // AUTHENTICATE_H
