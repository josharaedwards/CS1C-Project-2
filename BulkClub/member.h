#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QDate>
using namespace std;

const double REG_ANNUAL_DUE = 65.00;
const double EXEC_ANNUAL_DUE = 120.00;

class Member
{
    QString name;
    QDate expDate;

    int memberNum;
    double spentAmnt;
    double dueAmnt;
    double rebateAmnt;

    bool bIsExecutive;

public:
    //Constructors
    Member();
    Member(QString nameIn, QDate expDateIn, int memNumIn, double spentAmntIn, double rebateAmntIn, bool execIn);

    //Destructor
    ~Member();

    //Shallow & Deep Copy
    Member(const Member& other);
    void copy(Member other);

    //Overloaded Operators
    Member operator+(const double amnt)
    {
        Member m(*this);

        m.spentAmnt += amnt;

        return m;
    }

    Member operator-(const double amnt)
    {
        Member m(*this);

        m.spentAmnt -= amnt;

        return m;
    }

    //Setters & Getters
    void setName(QString nameIn);
    void setExpDate(QDate expDateIn);
    void setMemNum(int memNumIn);
    void setSpentAmnt(double spentAmntIn);
    void setDueAmnt(double dueAmntIn);
    void setRebateAmnt(double rebateAmntIn);
    void setExec(bool execIn);

    QString getName();
    QDate getExpDate();
    int getMemNum();
    double getSpentAmnt();
    double getDueAmnt();
    double getRebateAmnt();
    bool IsExec();  
};

#endif // MEMBER_H
