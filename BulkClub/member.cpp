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

    sales = other.sales;

    refreshSpentAmnt();
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

    refreshSpentAmnt();
}

Member::Member(QString nameIn, QDate expDateIn, int memNumIn, bool execIn)
{
    name = nameIn;
    expDate = expDateIn;
    memberNum = memNumIn;

    bIsExecutive = execIn;

    if(bIsExecutive)
    {
        dueAmnt = EXEC_ANNUAL_DUE;
    }
    else
    {
        dueAmnt = REG_ANNUAL_DUE;
    }

    refreshSpentAmnt();
}

Member::Member(QString nameIn, QDate expDateIn, int memNumIn, bool execIn, vector<Sale> salesIn)
{
    name = nameIn;
    expDate = expDateIn;
    memberNum = memNumIn;

    bIsExecutive = execIn;

    if(bIsExecutive)
    {
        dueAmnt = EXEC_ANNUAL_DUE;
    }
    else
    {
        dueAmnt = REG_ANNUAL_DUE;
    }

    sales = salesIn;

    refreshSpentAmnt();
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

void Member::setDueAmnt(double dueAmntIn)
{
    dueAmnt = dueAmntIn;
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
    refreshSpentAmnt();
    return spentAmnt;
}

double Member::getTaxAmnt()
{
    return spentAmnt*0.0775;
}

double Member::getDueAmnt()
{
    return dueAmnt;
}

double Member::getRebateAmnt()
{
    refreshRebateAmnt();
    return rebateAmnt;
}

bool Member::IsExec()
{
    return bIsExecutive;
}

void Member::refreshSpentAmnt()
{
    int size = sales.size();

    spentAmnt = 00.00;
    if(sales.size() > 0)
    {
        for(int i = 0; i < size; ++i)
        {
            spentAmnt += sales[i].getPrice() * sales[i].getQuantity();
        }
    }

    refreshRebateAmnt();
}

void Member::refreshRebateAmnt()
{
    rebateAmnt = spentAmnt * 0.02;
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

Sale Member::getSale(int index)
{
    return sales[index];
}

vector<Sale> Member::getSales()
{
    return sales;
}

bool Member::hasSale(Sale saleIn)
{
   bool isHere = false;
   int size = sales.size();

   for(int i = 0; i < size; ++i)
   {
       if(sales[i] == saleIn)
       {
           isHere = true;
       }
   }

   return isHere;
}

MemberStatus Member::checkMemberStatus()
{
    if(IsExec() && rebateAmnt < dueAmnt)
    {
        return DEMOTED;
    }
    else if(!IsExec() && rebateAmnt > dueAmnt)
    {
        return PROMOTED;
    }

    return NEUTRAL;
}

