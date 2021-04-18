/**
 *  @file dbmanager.cpp
 *  @brief Implementation file of DbManager Class
 */

#include "dbmanager.h"

DbManager::DbManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/johnn/OneDrive/Desktop/BulkClubData/bulk-club.sqlite");

    db.open();
}


DbManager::~DbManager()
{
    if (db.isOpen())
    {
        db.close();
    }
}


QSqlTableModel* DbManager::createMemberTable()
{
    QSqlTableModel *model = new QSqlTableModel;

    // load in the data from the member table
    model->setTable("Members");
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Member ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Membership"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));

    return model;
}


QSqlTableModel* DbManager::createSalesTable()
{
    QSqlTableModel *model = new QSqlTableModel;

    // load in the data from the sales table
    model->setTable("Sales");
    model->select();

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
