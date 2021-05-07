
#ifndef INVENTORY_H
#define INVENTORY_H

#include <QString>
#include <QDate>

class Inventory
{
    QString name;
    double price;
    int quantity;
    double total;

public:
    //Constructors
    Inventory();
    Inventory(QString nameIn, double priceIn, int quantityIn);

    //Destructors
    ~Inventory();

    //Shallow & Deep Copy
    Inventory(const Inventory& other);
    void copy(Inventory other);

    //Helper Functions
    void setName(QString nameIn);
    void setPrice(double priceIn);
    void setQuantity(int quantityIn);

    void refreshTotal();

    QString getName();
    double getPrice();
    int getQuantity();
    double getTotal();
};

#endif // INVENTORY_H
