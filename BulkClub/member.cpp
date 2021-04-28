#include "member.h"


Member::Member()
{
    name = "Jay Doe";
    expDate = QDate(1900, 1, 1);
    memberNum = 00000;

    spentAmnt = 00.00;
    rebateAmnt = 00.00;

    bIsExecutive = false;

    dueAmnt = REG_ANNUAL_DUE;
}

Member::Member(const Member& other)
{
    name = other.name;
    expDate = other.expDate;
    memberNum = other.memberNum;

    spentAmnt = other.spentAmnt;
    dueAmnt = other.dueAmnt;
    rebateAmnt = other.rebateAmnt;

    bIsExecutive = other.bIsExecutive;
}

void Member::copy(Member other)
{
    name = other.name;
    expDate = other.expDate;
    memberNum = other.memberNum;

    spentAmnt = other.spentAmnt;
    dueAmnt = other.dueAmnt;
    rebateAmnt = other.rebateAmnt;

    bIsExecutive = other.bIsExecutive;

}

Member::Member(QString nameIn, QDate expDateIn, int memNumIn, double spentAmntIn, double rebateAmntIn, bool execIn)
{
    name = nameIn;
    expDate = expDateIn;
    memberNum = memNumIn;

    spentAmnt = spentAmntIn;
    rebateAmnt = rebateAmntIn;

    bIsExecutive = execIn;

    if(bIsExecutive)
    {
        dueAmnt = EXEC_ANNUAL_DUE;
    }
    else
    {
        dueAmnt = REG_ANNUAL_DUE;
    }
}

Member::~Member()
{
    //Joshara (4/15/21)
    //For when/if we need to deallocate
}

void Member::setName(QString nameIn)
{
    name = nameIn;
}

void Member::setExpDate(QDate expDateIn)
{
    expDate = expDateIn;
}

void Member::setMemNum(int memNumIn)
{
    memberNum = memNumIn;
}

void Member::setSpentAmnt(double spentAmntIn)
{
    spentAmnt = spentAmntIn;
}

void Member::setDueAmnt(double dueAmntIn)
{
    dueAmnt = dueAmntIn;
}

void Member::setRebateAmnt(double rebateAmntIn)
{
    rebateAmnt = rebateAmntIn;
}

void Member::setExec(bool execIn)
{
    bIsExecutive = execIn;
}

QString Member::getName()
{
    return name;
}

QDate Member::getExpDate()
{
    return expDate;
}

int Member::getMemNum()
{
    return memberNum;
}

double Member::getSpentAmnt()
{
    return spentAmnt;
}

double Member::getDueAmnt()
{
    return dueAmnt;
}

double Member::getRebateAmnt()
{
    return rebateAmnt;
}

bool Member::IsExec()
{
    return bIsExecutive;
}

void Member::addSale(Sale sale)
{
    sales.push_back(sale);
}

void Member::addSales(vector<Sale> salesIn)
{
    int size = salesIn.size();

    for(int i = 0; i < size; ++i)
    {
        sales.push_back(salesIn[i]);
    }
}

vector<Sale> Member::getSales()
{
    return sales;
}
