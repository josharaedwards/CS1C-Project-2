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
 * @class Sale
 * @brief class representing a sale
 * @details used mostly in a vector of sales, populated from an sql file
 */
class Sale
{
    QString name;   /// @var QString name - name of the product
    QDate date;     /// @var QDate date -date of purchas
    int memberNum;  /// @var int memberNum -member ID of member who purchased item
    double price;   /// @var double price -price of the item
    int quantity;   /// @var int quantity -quantity bought by member

public:
    //Constructors
    /**
     * @brief Sales class default constructor
     * @details initialized data members with default values
     */
    Sale();
    /**
     * @brief Sales class overloaded constructor
     * @details populates all sale data members with passed in values
     * @param QString nameIn -passed in product name to be assigned to sale
     * @param QDate dateIn -passed in purchase date to be assigned to sale
     * @param int memNumIn -passed in member ID to be assigned to sale
     * @param double priceIn -passed in price to be assigned to sale
     * @param int quantityIn -passed in quantity to be assigned to sale
     */
    Sale(QString nameIn, QDate dateIn, int memNumIn, double priceIn, int quantityIn);

    //Destructors
    /**
     * @brief Sales class destructor
     * @details runs when Sales goes out of scope
     */
    ~Sale();

   //Overloaded Operators
    /**
     * @brief overloaded == operator
     * @details compares passed in sale to current sale, returns true if they are the same
     * @param Sale other -passed in sale to be compared
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
    * @brief Copy constructor
    * @details copies passed in Sale to curret sale
    * @param const Sale& other -Sale object to be copied
    */
    Sale(const Sale& other);
    /**
     * @brief copy function
     * @details copies passed in object to the current object
     * @param Sale other -Sale object to be copied
     */
    void copy(Sale other);
    //Helper Functions
    /**
     * @brief setName
     * @details sets the name of the product as the passed in string
     * @param QString nameIn -product name to be assigned to the sale
     */
    void setName(QString nameIn);
    /**
     * @brief setDate
     * @details sets the date of the sale to the passed in QDate object
     * @param QDate dateIn -QDate to be assigned to the Sale date
     */
    void setDate(QDate dateIn);
    /**
     * @brief setMemNum function
     * @details sets the member Number to the passed in int
     * @param int memNumIn -member number to be assigned to the Sale
     */
    void setMemNum(int memNumIn);
    /**
     * @brief setPrice
     * @details sets the item price to the passed in double
     * @param double priceIn -sets the
     */
    void setPrice(double priceIn);
    /**
     * @brief setQuantity
     * @details
     * @param int quantityIn -
     */
    void setQuantity(int quantityIn);
    /**
     * @brief getName
     * @details
     */
    QString getName();
    /**
     * @brief getDate
     * @details
     */
    QDate getDate();
    /**
     * @brief getMemNum
     * @details
     */
    int getMemNum();
    /**
     * @brief getPrice
     * @details
     */
    double getPrice();
    /**
     * @brief getQuantity
     * @details
     */
    int getQuantity();
};

#endif // SALE_H
