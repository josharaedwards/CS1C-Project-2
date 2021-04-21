#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

#include <QString>
using namespace std;

enum loginStatus { FAILED, MANAGER, ADMIN };

class Authenticate
{
    QString username;
    QString password;
    loginStatus state;

public:
    Authenticate();
    ~Authenticate();
    loginStatus attempt(QString userIn, QString passIn);
    loginStatus getState();
};

#endif // AUTHENTICATE_H
