#include "helperLib.h"


Member search(vector<Member> members, int memNumIn, bool& bSucceed)
{
    Member m;
    int size = members.size();

    for(int i = 0; i < size; ++i)
    {
        if(members[i].getMemNum() == memNumIn)
        {
            m.copy(members[i]);
            bSucceed = true;
            return m;
        }
    }

    return m;
}

Member search(vector<Member> members, QString nameIn, bool& bSucceed)
{
    Member m;
    int size = members.size();

    for(int i = 0; i < size; ++i)
    {
        if(members[i].getName() == nameIn)
        {
            m.copy(members[i]);
            bSucceed = true;
            return m;
        }
    }

    return m;
}

vector<Member> searchMult(vector<Member> members, bool execIn)
{
    vector<Member> memsOut;
    int size = members.size();

    for(int i = 0; i < size; ++i)
    {
        if(members[i].IsExec() == execIn)
        {
            memsOut.push_back(members[i]);
        }
    }

    return memsOut;
}

vector<Member> searchMult(vector<Member> members, QDate expDateIn)
{
    vector<Member> memsOut;
    int size = members.size();
    int inMonth = expDateIn.month();
    int inYear = expDateIn.year();

    for(int i = 0; i < size; ++i)
    {
        int memMonth = members[i].getExpDate().month();
        int memYear = members[i].getExpDate().year();

        if(memMonth == inMonth && memYear == inYear)
        {
            memsOut.push_back(members[i]);
        }
    }

    return memsOut;
}

vector<Member> sortBy(vector<Member> members, SortType sort)
{
    vector<Member> memsOut = members;

    switch(sort)
    {
    case NAME:
        byName(memsOut);
        break;
    case EXP:
        byExp(memsOut);
        break;
    case NUM:
        byNum(memsOut);
        break;
    case SPENT_AMNT:
        bySpentAmnt(memsOut);
        break;
    case REBATE_AMNT:
        byRebateAmnt(memsOut);
        break;
    case EXEC:
        byExec(memsOut);
        break;
    default:
        byName(memsOut);
        break;
    }

    return memsOut;
}

void byName(vector<Member>& members)
{
    int numOfEntries = members.size();

    for(int i = 1; i < numOfEntries - 1; ++i)
    {
        for(int j = i + 1; j < numOfEntries; ++j)
        {
            bool result = isGreaterThan(members[i].getName(), members[j].getName());
            Member temp;

            if(result)
            {
                temp = members[i];
                members[i] = members[j];
                members[j] = temp;
            }
        }
    }
}

void byExp(vector<Member>& members)
{
    int numOfEntries = members.size();

    for(int i = 1; i < numOfEntries - 1; ++i)
    {
        for(int j = i + 1; j < numOfEntries; ++j)
        {
            bool result = isGreaterThan(members[i].getExpDate(), members[j].getExpDate());
            Member temp;

            if(result)
            {
                temp = members[i];
                members[i] = members[j];
                members[j] = temp;
            }
        }
    }
}

void byNum(vector<Member>& members)
{
    int numOfEntries = members.size();

    for(int i = 1; i < numOfEntries - 1; ++i)
    {
        for(int j = i + 1; j < numOfEntries; ++j)
        {
            bool result = isGreaterThan(members[i].getMemNum(), members[j].getMemNum());
            Member temp;

            if(result)
            {
                temp = members[i];
                members[i] = members[j];
                members[j] = temp;
            }
        }
    }
}

void bySpentAmnt(vector<Member>& members)
{
    int numOfEntries = members.size();

    for(int i = 1; i < numOfEntries - 1; ++i)
    {
        for(int j = i + 1; j < numOfEntries; ++j)
        {
            bool result = isGreaterThan(members[i].getSpentAmnt(), members[j].getSpentAmnt());
            Member temp;

            if(result)
            {
                temp = members[i];
                members[i] = members[j];
                members[j] = temp;
            }
        }
    }
}

void byRebateAmnt(vector<Member>& members)
{
    int numOfEntries = members.size();

    for(int i = 1; i < numOfEntries - 1; ++i)
    {
        for(int j = i + 1; j < numOfEntries; ++j)
        {
            bool result = isGreaterThan(members[i].getRebateAmnt(), members[j].getRebateAmnt());
            Member temp;

            if(result)
            {
                temp = members[i];
                members[i] = members[j];
                members[j] = temp;
            }
        }
    }
}

bool isGreaterThan(QString first, QString second)
{
    QChar firstLetter = first[0];
    QChar secondLetter = second[0];

    if(firstLetter > secondLetter)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isGreaterThan(QDate first, QDate second)
{
    if(first > second)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isGreaterThan(double first, double second)
{
    if(first > second)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isGreaterThan(int first, int second)
{
    if(first > second)
    {
        return true;
    }
    else
    {
        return false;
    }
}
