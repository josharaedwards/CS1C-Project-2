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
