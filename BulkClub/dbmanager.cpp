/**
 *  @file dbmanager.cpp
 *  @brief Implementation file of DbManager Class
 */

#include "dbmanager.h"

extern vector<Member> members;
extern vector<Sale> sales;
extern vector<Inventory> inventory;

DbManager::DbManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bulk-club.sqlite");

    db.open();
}


DbManager::~DbManager()
{
    QSqlQuery query(db);

    qDebug() << query.driver()->hasFeature(QSqlDriver::NamedPlaceholders);

    /// @brief Deleting all contents from the Members table in the databse
    query.exec("DELETE FROM Members");

    /// @brief Inserting all contents from the global members vector into the database
    QVariant name, memNum, memType, expDate;
    for (unsigned int i = 0; i < members.size(); i++)
    {
        name = members[i].getName();
        memNum = members[i].getMemNum();
        if (members[i].IsExec())
        {
            memType = "Executive";
        }
        else
        {
            memType = "Regular";
        }
        expDate = members[i].getExpDate().toString("M/d/yyyy");

        qDebug() << name << " " << memNum << " " << memType << " " << expDate;

        query.prepare("INSERT INTO Members (Name, Member ID, Membership, Date) VALUES (?, ?, ?, ?)");

        query.addBindValue(name);
        query.addBindValue(memNum);
        query.addBindValue(memType);
        query.addBindValue(expDate);

        query.exec();
    }

    qDebug() << query.lastError();
    qDebug() << query.executedQuery();

    /// @brief Deleting all contents from the Members table in the databse
    // query.exec("DELETE FROM Sales");

    /// @brief Inserting all contents from the global members vector into the database


    /// @brief Deleting all contents from the Members table in the databse
    // query.exec("DELETE FROM Inventory");

    /// @brief Inserting all contents from the global members vector into the database


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


QSqlTableModel* DbManager::createInventoryTable()
{
    /// @brief Creates a new QSqlTableModel for the Inventory table
    QSqlTableModel *model = new QSqlTableModel;

    /// @brief Load in the data from the Inventory table of the database
    model->setTable("Inventory");
    model->select();

    /// @brief Sets the header data for the Inventory table
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Product"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Price"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantity"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Total Revenue"));

    model->setSort(0, Qt::AscendingOrder);

    /// @brief adds remaining data to inventory model
    //may need to clear information from inventory table then build model from vector>Inventory>
    //model->clear();
    int vecSize = inventory.size();
    QSqlRecord record = model->record();
    QVariant name, price, quantity, total;
    for(int i = 0; i < vecSize; i++)
    {
        name.setValue(inventory[i].getName());
        price.setValue(inventory[i].getPrice());
        quantity.setValue(inventory[i].getQuantity());
        total.setValue(inventory[i].getTotal());

        record.clearValues();
        record.setValue(0, name);
        record.setValue(1, price);
        record.setValue(2, quantity);
        record.setValue(3, total);
        if(model->setRecord(i, record))
        {
            qDebug()<<"Successfully inserted record!";
            model->submitAll();
        }
        else
        {
            qDebug()<<"Error inserting record!";
            db.rollback();
        }
    }
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);



    return model;
}


vector<Member> DbManager::popMemVec()
{
    Member newMem;
    vector<Member> memsOut;
    QSqlQuery queryMem("SELECT * FROM Members", db);

    while(queryMem.next())
    {
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


vector<Sale> DbManager::popSaleVec()
{
    Sale newSale;
    vector<Sale> salesOut;

    QSqlQuery querySale("SELECT * FROM Sales", db);

    while(querySale.next())
    {
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

void DbManager::popInvVec()
{
    int saleSize = sales.size();

    for(int i = 0; i < saleSize; i++)
    {
        // if current sale.name is in inventory vec, sum existing quantity with sale quantity
        int quantityIndex = findInvIndex(sales[i].getName());
        if(isInInventory(sales[i].getName()) && quantityIndex > -1)
        {
            int tempQuantity = inventory[quantityIndex].getQuantity() + sales[i].getQuantity();
            inventory[quantityIndex].setQuantity(tempQuantity);
        }
        else // adds first instance of sale to inventory vec
        {
            Inventory temp_item;

            temp_item.setName(sales[i].getName());
            temp_item.setPrice(sales[i].getPrice());
            temp_item.setQuantity((sales[i].getQuantity()));
            inventory.push_back(temp_item);
        }
    }
}

bool DbManager::isInInventory(QString searchName)
{
    bool found = false;
    int vecSize = inventory.size();

    for(int i = 0; i < vecSize; i++)
    {
        if(inventory[i].getName() == searchName)
        {
            found = true;
            return found;
        }
    }
    return found;
}

int DbManager::findInvIndex(QString itemName)
{
    int foundIndex;
    int vecSize = inventory.size();

    for(int i = 0; i < vecSize; i++)
    {
        if(inventory[i].getName() == itemName)
        {
            foundIndex = i;
            return foundIndex;
        }
        else
        {
            foundIndex = -1;
        }
    }
    return foundIndex;
}
