/**
 *  @file inventory.h
 *  @brief Contains the definition of the Inventory Class
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <QString>
#include <QDate>

/**
 * @class
 * @brief
 * @details
 */
class Inventory
{
    QString name;   /// @var
    double price;   /// @var
    int quantity;   /// @var
    double total;   /// @var

public:
    //Constructors
    /**
     * @brief
     * @details
     */
    Inventory();
    /**
     * @brief
     * @details
     * @param
     * @param
     * @param
     */
    Inventory(QString nameIn, double priceIn, int quantityIn);

    //Destructors
    /**
     * @brief
     * @details
     */
    ~Inventory();

    //Shallow & Deep Copy
    /**
     * @brief
     * @details
     * @param
     */
    Inventory(const Inventory& other);
    /**
     * @brief
     * @details
     * @param
     */
    void copy(Inventory other);

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
    void refreshTotal();
    /**
     * @brief
     * @details
     */
    QString getName();
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
    /**
     * @brief
     * @details
     */
    double getTotal();
};

#endif // INVENTORY_H
