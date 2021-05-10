#include "authenticate.h"

Authenticate::Authenticate()
{
    username = "";
    password = "";
    state = FAILED;

    login_db = QSqlDatabase::addDatabase("QSQLITE", "UserInfo");
    login_db.setDatabaseName("UserPass.sqlite");

    login_db.open();
}

Authenticate::~Authenticate()
{
    if (login_db.isOpen())
    {
        login_db.close();
    }
}

/// @brief returns login status using sqlite UserPass database file
loginStatus Authenticate::attempt(QString userIn, QString passIn)
{
    QSqlQuery queryDev("SELECT username, password FROM developers", login_db);
    QSqlQuery queryMan("SELECT username, password FROM managers", login_db);
    while(queryDev.next()){
        if(userIn == queryDev.value(0).toString() && passIn == queryDev.value(1).toString()){
            state = ADMIN;
        }
    }
    while(queryMan.next()){
        if(userIn == queryMan.value(0).toString() && passIn == queryMan.value(1).toString()) {
            state = MANAGER;
        }
    }

    return state;
}

loginStatus Authenticate::getState()
{
    return state;
}

void Authenticate::logout()
{
    state = FAILED;
}
