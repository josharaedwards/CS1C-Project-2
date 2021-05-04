/**
 *  @file member.h
 *  @brief Contains the definition of the Member Class
 */

#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QDate>
#include <vector>
#include "sale.h"
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

    vector<Sale> sales;

public:
    //Constructors
    Member();
    Member(QString nameIn, QDate expDateIn, int memNumIn, bool execIn);
    Member(QString nameIn, QDate expDateIn, int memNumIn, bool execIn, vector<Sale> salesIn);

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

    //Helper Functions
    void setName(QString nameIn);
    void setExpDate(QDate expDateIn);
    void setMemNum(int memNumIn);
    void setDueAmnt(double dueAmntIn);
    void setExec(bool execIn);

    void refreshSpentAmnt();
    void refreshRebateAmnt();

    void addSale(Sale sale);
    void addSales(vector<Sale> salesIn);

    QString getName();
    QDate getExpDate();
    int getMemNum();
    double getSpentAmnt();
    double getTaxAmnt();
    double getDueAmnt();
    double getRebateAmnt();
    bool IsExec();  

    Sale getSale(int index);
    vector<Sale> getSales();
    bool hasSale(Sale saleIn);
};

#endif // MEMBER_H
