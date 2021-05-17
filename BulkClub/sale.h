/**
 *  @file sale.h
 *  @brief Contains the definition of the Sale Class
 */

#ifndef SALE_H
#define SALE_H

#include <QString>
#include <QDate>
using namespace std;

/**
 * @class
 * @brief
 * @details
 */
class Sale
{
    QString name;   /// @var
    QDate date;     /// @var
    int memberNum;  /// @var
    double price;   /// @var
    int quantity;   /// @var

public:
    //Constructors
    /**
     * @brief
     * @details
     */
    Sale();
    /**
     * @brief
     * @details
     * @param
     * @param
     * @param
     * @param
     * @param
     */
    Sale(QString nameIn, QDate dateIn, int memNumIn, double priceIn, int quantityIn);

    //Destructors
    /**
     * @brief
     * @details
     */
    ~Sale();

   //Overloaded Operators
    /**
     * @brief
     * @details
     * @param
     */
   bool operator==(Sale other)
   {
       if(name == other.name &&
               date == other.date &&
               memberNum == other.memberNum &&
               price == other.price &&
               quantity == other.quantity)
       {
           return true;
       }

       return false;
   }


    //Shallow & Deep Copy
   /**
    * @brief
    * @details
    * @param
    */
    Sale(const Sale& other);
    /**
     * @brief
     * @details
     * @param
     */
    void copy(Sale other);
    /**
     * @brief
     * @details
     */
    //Helper Functions
    /**
     * @brief
     * @details
     * @param
     */
    void setName(QString nameIn);
    /**
     * @brief
     * @details
     * @param
     */
    void setDate(QDate dateIn);
    /**
     * @brief
     * @details
     * @param
     */
    void setMemNum(int memNumIn);
    /**
     * @brief
     * @details
     * @param
     */
    void setPrice(double priceIn);
    /**
     * @brief
     * @details
     * @param
     */
    void setQuantity(int quantityIn);
    /**
     * @brief
     * @details
     */
    QString getName();
    /**
     * @brief
     * @details
     */
    QDate getDate();
    /**
     * @brief
     * @details
     */
    int getMemNum();
    /**
     * @brief
     * @details
     */
    double getPrice();
    /**
     * @brief
     * @details
     */
    int getQuantity();
};

#endif // SALE_H
