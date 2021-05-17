
#ifndef INVENTORY_H
#define INVENTORY_H

#include <QString>
#include <QDate>

/**
 * @class Inventory
 *
 * @brief A user-defined object to keep track of information
 * relevant to an entry in the inventory
 */
class Inventory
{
    ///@var name A QString holding the name of an item in the inventory
    QString name;
    ///@var price A double holding the price of an item in the inventory
    double price;
    ///@var quantity An integer holding the amount of this item in the inventory
    int quantity;
    ///@var total The calculated total which is retrieved by calling refreshTotal()
    double total;

public:
    //Constructors
    ///@brief Inventory default constructor
    Inventory();
    /**
    * @brief Inventory constructor that accepts a name, price,
    * and quantity. It calculates the total by calling refreshTotal()
    * @param nameIn the name of the item being constructed
    * @param priceIn the price of the item being constructed
    * @param quantityIn the quantity of the item being constructed
    */

    Inventory(QString nameIn, double priceIn, int quantityIn);

    //Destructors
    ///@brief Inventory destructor
    ~Inventory();

    //Shallow & Deep Copy
    /**
    *@brief copy constructor for creating a shallow copy
    *@param other the item to copy from by reference
    */
    Inventory(const Inventory& other);
    /**
    *@brief copy constructor for creating a deep copy
    *@param other the item to copy from by value
    */
    void copy(Inventory other);

    //Helper Functions
    /**
    *@brief sets the object's name
    *@param nameIn the QString to set the item's name to
    */
    void setName(QString nameIn);
    /**
    *@brief sets the object's price
    *@param priceIn the double to set the item's price to
    */
    void setPrice(double priceIn);
    /**
    *@brief sets the object's quantity
    *@param quantityIn the int to set the item's quantity to
    */
    void setQuantity(int quantityIn);

    /**
    *@brief refreshes the total price for the object by multiplying
    *the quantity by the price
    */
    void refreshTotal();

    ///@brief returns the object's name as a QString
    QString getName();
    ///@brief returns the object's price as a double
    double getPrice();
    ///@brief returns the object's quantity as an int
    int getQuantity();
    ///@brief returns the object's total as a double
    double getTotal();
};

#endif // INVENTORY_H
