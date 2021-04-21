#include "authenticate.h"

Authenticate::Authenticate()
{
    username = "";
    password = "";
    state = failed;
}

loginStatus Authenticate::attempt(QString userIn, QString passIn)
{
    if(userIn == "username" && passIn == "password"){
        state = admin;
    }
    return state;
}

loginStatus Authenticate::isLogged()
{
    return state;
}
