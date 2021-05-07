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

vector<Member> sort(vector<Member> members, SortType sortBy)
{
    vector<Member> memsOut = members;

    switch(sortBy)
    {
    case NAME:
        sortByName(memsOut);
        break;
    case EXP:
        sortByExp(memsOut);
        break;
    case NUM:
        sortByNum(memsOut);
        break;
    case SPENT_AMNT:
        sortBySpentAmnt(memsOut);
        break;
    case REBATE_AMNT:
        sortByRebateAmnt(memsOut);
        break;
    default:
        sortByName(memsOut);
        break;
    }

    return memsOut;
}

void sortByName(vector<Member>& members)
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

void sortByExp(vector<Member>& members)
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

void sortByNum(vector<Member>& members)
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

void sortBySpentAmnt(vector<Member>& members)
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

void sortByRebateAmnt(vector<Member>& members)
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

void saleToMembers(vector<Member>& members, Sale sale)
{
    int ID = sale.getMemNum();
    int size = members.size();

    for(int i = 0; i < size; ++i)
    {
        if(members[i].getMemNum() == ID)
        {
            members[i].addSale(sale);
        }
    }
}

void salesToMembers(vector<Member>& members, vector<Sale> sales)
{
    int size = sales.size();

    for(int i = 0; i < size; ++i)
    {
        saleToMembers(members, sales[i]);
    }
}

QAbstractItemModel* createMemberModel(QWidget* parent, vector<Member> members)
{
    QStandardItemModel *model = new QStandardItemModel(0, 4, parent);

    /// @brief Creating an object for every header and labelling them appropriately.
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Member ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Membership"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));

    for(unsigned int i = 0; i < members.size(); i++)
    {
        addMember(model, members[i]);
    }

    return model;
}

void addMember(QAbstractItemModel* model, Member memIn)
{
    /// @brief Adds a row to the model from the top.
    model->insertRow(0);

    /// @brief Adds the data for a member into the model, similar to a two dimensional array.
    model->setData(model->index(0, 0), memIn.getName());
    model->setData(model->index(0, 1), memIn.getMemNum());

    if (memIn.IsExec())
    {
        model->setData(model->index(0, 2), QObject::tr("Executive"));
    }
    else
    {
        model->setData(model->index(0, 2), QObject::tr("Regular"));
    }

    model->setData(model->index(0, 3), memIn.getExpDate().toString("M/d/yyyy"));
}

QAbstractItemModel* createSalesModel(QWidget* parent, vector<Sale> sales)
{
    QStandardItemModel *model = new QStandardItemModel(0, 5, parent);

    /// @brief Creating an object for every header and labelling them appropriately.
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Member ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Product"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Price"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantity"));

    for(unsigned int i = 0; i < sales.size(); i++)
    {
        addSale(model, sales[i]);
    }

    return model;
}

void addSale(QAbstractItemModel* model, Sale saleIn)
{
    /// @brief Adds a row to the model from the top.
    model->insertRow(0);

    /// @brief Adds the data for a sale into the model, similar to a two dimensional array.
    model->setData(model->index(0, 0), saleIn.getDate().toString("M/d/yyyy"));
    model->setData(model->index(0, 1), saleIn.getMemNum());
    model->setData(model->index(0, 2), saleIn.getName());
    model->setData(model->index(0, 3), saleIn.getPrice());
    model->setData(model->index(0, 4), saleIn.getQuantity());
}
