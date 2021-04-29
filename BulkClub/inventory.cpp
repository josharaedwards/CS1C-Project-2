#include "inventory.h"

Inventory::Inventory()
{
    name = "None";
    price = 00.00;
    quantity = 0;
    total = 00.00;
}

Inventory::Inventory(const Inventory& other)
{
    name = other.name;
    price = other.price;
    quantity = other.quantity;
    total = other.total;
}

void Inventory::copy(Inventory other)
{
    name = other.name;
    price = other.price;
    quantity = other.quantity;
    total = other.total;
}

Inventory::Inventory(QString nameIn, double priceIn, int quantityIn)
{
    name = nameIn;
    price = priceIn;
    quantity = quantityIn;

    refreshTotal();
}

Inventory::~Inventory()
{
    //Joshara (4/27/21)
    //For when/if we need to deallocate
}

void Inventory::setName(QString nameIn)
{
    name = nameIn;
}

void Inventory::setPrice(double priceIn)
{
    price = priceIn;
    refreshTotal();
}

void Inventory::setQuantity(int quantityIn)
{
    quantity = quantityIn;
    refreshTotal();
}

void Inventory::refreshTotal()
{
    total = price * quantity;
}

QString Inventory::getName()
{
    return name;
}

double Inventory::getPrice()
{
    return price;
}

int Inventory::getQuantity()
{
    return quantity;
}

double Inventory::getTotal()
{
    return total;
}
