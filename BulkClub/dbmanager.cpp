/**
 *  @file dbmanager.cpp
 *  @brief Implementation file of DbManager Class
 */

#include "dbmanager.h"

DbManager::DbManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bulk-club.sqlite");

    db.open();
}


DbManager::~DbManager()
{
    /// @brief If the database connection is open, then it is closed
    if (db.isOpen())
    {
        db.close();
    }
}

QSqlTableModel* DbManager::createMemberTable()
{
    /// @brief Creates a new QSqlTableModel for the Member table
    QSqlTableModel *model = new QSqlTableModel;

    /// @brief Load in the data from the Member table of the database
    model->setTable("Members");
    model->select();

    /// @brief Sets the header data for the Member table
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Member ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Membership"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));

    return model;
}


QSqlTableModel* DbManager::createSalesTable()
{
    /// @brief Creates a new QSqlTableModel for the Sales table
    QSqlTableModel *model = new QSqlTableModel;

    /// @brief Load in the data from the Sales table of the database
    model->setTable("Sales");
    model->select();

    /// @brief Sets the header data for the Sales table
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Member ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Product"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Price"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantity"));

    return model;
}

void DbManager::addMember(Member newMember)
{

}


void DbManager::removeMember()
{

}


void DbManager::addSale()
{

}


void DbManager::removeSale()
{

}

vector<Member> DbManager::popMemVec(){
    Member newMem;
    vector<Member> memsOut;
    QSqlQuery queryMem("SELECT * FROM Members", db);

    while(queryMem.next()){

        //set newMem member values
        newMem.setName(queryMem.value(0).toString());
        newMem.setMemNum(queryMem.value(1).toInt());
        if(queryMem.value(2).toString() == "Executive")
            newMem.setExec(true);
        else
            newMem.setExec(false);
        newMem.setExpDate(QDate::fromString(queryMem.value(3).toString(), "M/d/yyyy"));

        //assign newMem to next vector element
        memsOut.push_back(newMem);

    }
    return memsOut;
}

vector<Sale> DbManager::popSaleVec(){
    Sale newSale;
    vector<Sale> salesOut;

    QSqlQuery querySale("SELECT * FROM Sales", db);

    while(querySale.next()){

        //set newMem member values
        newSale.setDate(QDate::fromString(querySale.value(0).toString(), "M/d/yyyy"));
        newSale.setMemNum(querySale.value(1).toInt());
        newSale.setName(querySale.value(2).toString());
        newSale.setPrice(querySale.value(3).toFloat());
        newSale.setQuantity(querySale.value(4).toInt());

        //assign newMem to next vector element
        salesOut.push_back(newSale);

    }
    return salesOut;
}
