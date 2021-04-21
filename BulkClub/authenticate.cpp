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

Authenticate::~Authenticate(){
    if (login_db.isOpen())
    {
        login_db.close();
    }
}

/// @brief returns login status using sqlite UserPass database file
loginStatus Authenticate::attempt(QString userIn, QString passIn)
{
    QSqlQuery queryUser("SELECT username, password FROM UserInfo", login_db);
    while(queryUser.next()){
        if(userIn == queryUser.value(0).toString() && passIn == queryUser.value(1).toString()){
            state = ADMIN;
        }
    }

    return state;
}

loginStatus Authenticate::getState()
{
    return state;
}
