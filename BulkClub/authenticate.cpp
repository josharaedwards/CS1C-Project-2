#include "authenticate.h"

Authenticate::Authenticate()
{
    username = "";
    password = "";
    state = FAILED;
}

Authenticate::~Authenticate(){

}

loginStatus Authenticate::attempt(QString userIn, QString passIn)
{
    if(userIn == "username" && passIn == "password"){
        state = ADMIN;
    }
    return state;
}

loginStatus Authenticate::getState()
{
    return state;
}
