#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

#include <QString>
using namespace std;

enum loginStatus { failed, manager, admin };

class Authenticate
{
    QString username;
    QString password;
    loginStatus state;

public:
    Authenticate();
    ~Authenticate(){}
    loginStatus attempt(QString userIn, QString passIn);
    loginStatus isLogged();
};

#endif // AUTHENTICATE_H
