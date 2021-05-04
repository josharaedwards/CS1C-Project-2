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

enum loginStatus { FAILED, MANAGER, ADMIN };

class Authenticate
{
    QString username;
    QString password;
    loginStatus state;
    QSqlDatabase login_db;
public:
    Authenticate();
    ~Authenticate();
    loginStatus attempt(QString userIn, QString passIn);
    loginStatus getState();
    void logout();
};

#endif // AUTHENTICATE_H
