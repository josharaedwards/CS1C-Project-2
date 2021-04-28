#ifndef SALE_H
#define SALE_H

#include <QString>
#include <QDate>
using namespace std;

class Sale
{
    QString name;
    QDate date;
    int memberNum;
    double price;
    int quantity;

public:
    //Constructors
    Sale();
    Sale(QString nameIn, QDate dateIn, int memNumIn, double priceIn, int quantityIn);

    //Destructors
    ~Sale();

    //Shallow & Deep Copy
    Sale(const Sale& other);
    void copy(Sale other);

    //Helper Functions
    void setName(QString nameIn);
    void setDate(QDate dateIn);
    void setMemNum(int memNumIn);
    void setPrice(double priceIn);
    void setQuantity(int quantityIn);

    QString getName();
    QDate getDate();
    int getMemNum();
    double getPrice();
    int getQuantity();
};

#endif // SALE_H