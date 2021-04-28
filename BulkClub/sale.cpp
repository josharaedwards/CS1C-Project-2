#include "sale.h"

Sale::Sale()
{
    name = "None";
    date = QDate(1900, 1, 1);
    memberNum = 00000;
    price = 00.00;
    quantity = 0;
}

Sale::Sale(const Sale& other)
{
    name = other.name;
    date = other.date;
    memberNum = other.memberNum;
    price = other.price;
    quantity = other.quantity;
}

void Sale::copy(Sale other)
{
    name = other.name;
    date = other.date;
    memberNum = other.memberNum;
    price = other.price;
    quantity = other.quantity;
}

Sale::Sale(QString nameIn, QDate dateIn, int memNumIn, double priceIn, int quantityIn)
{
    name = nameIn;
    date = dateIn;
    memberNum = memNumIn;
    price = priceIn;
    quantity = quantityIn;
}

Sale::~Sale()
{
    //Joshara (4/27/21)
    //For when/if we need to deallocate
}

void Sale::setName(QString nameIn)
{
    name = nameIn;
}

void Sale::setDate(QDate dateIn)
{
    date = dateIn;
}

void Sale::setMemNum(int memNumIn)
{
    memberNum = memNumIn;
}

void Sale::setPrice(double priceIn)
{
    price = priceIn;
}

void Sale::setQuantity(int quantityIn)
{
    quantity = quantityIn;
}

QString Sale::getName()
{
    return name;
}

QDate Sale::getDate()
{
    return date;
}

int Sale::getMemNum()
{
    return memberNum;
}

double Sale::getPrice()
{
    return price;
}

int Sale::getQuantity()
{
    return quantity;
}
