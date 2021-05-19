/**
 *  @file salespopup.h
 *  @brief Contains the definition of the SalesPopup window
 */

#ifndef SALESPOPUP_H
#define SALESPOPUP_H

#include "member.h"
#include "sale.h"
#include "helperLib.h"

#include <QDialog>

namespace Ui {
class SalesPopup;
}

/**
 * @class SalesPopup
 * @brief Generates a detailed sales report for any given day
 * @details Includes the total revenue, amount of Regular and Executive shoppers, and able to filter sales by membership
 */
class SalesPopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief SalesPopup
     * @details The default constructor of the SalesPopup class
     * @param dateIndex The day of sales records to search for
     * @param idIndex The member ID of the person pressed in the sales view
     * @param parent The parenting widget
     */
    explicit SalesPopup(QString dateIndex, int idIndex, QWidget *parent = nullptr);
    /**
     * @brief ~SalesPopup
     * @details The default destructor of the SalesPopup class
     */
    ~SalesPopup();
    /**
     * @brief getSaleMembers
     * @details Retrieves a vector containing all members with purchases on the same date as the key
     * @param key A sale associated with the member pressed, to search for sales of that same day
     */
    vector<Member> getSaleMembers(Sale key);
    /**
     * @brief populateSaleCells
     * @details Populates the sales table with a vector of members that had sales on the given date
     * @param saleMembers All members that made a purchase on the date described by the SalesPopup
     */
    void populateSaleCells(vector<Member> saleMembers);
    /**
     * @brief populateSummaryCells
     * @details Populates the summary table with the total, number of executive sales, and number of regular sales
     * @param saleMembers A vector of all members that made purchases on the date described by the SalesPopup
     */
    void populateSummaryCells(vector<Member> saleMembers);
    /**
     * @brief indexToText
     * @details Generates the text to be placed in individual cells of the memberInfoTable
     * @param curMember The member to retrieve information for
     * @param columnIndex An integer representing what column is being filled with the returned QString
     * @return A QString containing the data to be dispayed in the main table of the SalesPopup
     */
    QString indexToText(Member curMember, int columnIndex);
    /**
     * @brief updateTotal
     * @details Calculates the total revenue for each purchase displayed by the main view of the SalesPopup
     * @param
     */
    void updateTotal(vector<Member> saleMembers);

private slots:
    /**
     * @brief on_memTypeCombo_currentIndexChanged
     * @details The index of the combo box representing the membership type to be displayed in the purchases table
     * @param index An integer representing the type of membership to filter the view by--Executive, Regular, or Any
     */
    void on_memTypeCombo_currentIndexChanged(int index);

private:
    Ui::SalesPopup *ui; ///@var ui The user interface, a variable to interact with the objects generated from the Qt form
};

#endif // SALESPOPUP_H
