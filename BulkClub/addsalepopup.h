/**
 * @file addsalepopup.h
 * @brief contains definition of AddSalePopup window
 */

#ifndef ADDSALEPOPUP_H
#define ADDSALEPOPUP_H

#include <QDialog>
#include "helperLib.h"

namespace Ui {
class AddSalePopup;
}
/**
 * @class
 * @brief
 * @details
 */
class AddSalePopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief addSalePopup constructor
     * @details constructs the
     * @param Sale -object representing sale to be added
     * @param QWidget* -address of QItem passed in
     */
    explicit AddSalePopup(Sale newSale, QWidget *parent = nullptr);
    /**
     * @brief AddSalePopup destructor
     * @details destroys the AddSalePopup window
     */
    ~AddSalePopup();
    /**
     * @brief getAnotherSale function
     * @details returns true if the user wants to add another sale
     */
    bool getAnotherSale();
    /**
     * @brief getConfirmSales
     * @details returns true if sales are confirmed
     */
    bool getConfirmSales();
    /**
     * @brief addSales vector
     * @details contains a vector of the sales added
     */
    static vector<Sale> addSales;

private slots:
    /**
     * @brief addSaleButton clicked event
     * @details opens the "add sales" tab when clicked
     */
    void on_addSaleButton_released();
    /**
     * @brief confirmButton clicked event
     * @details closes window and saves the added information
     */
    void on_confirmButton_released();
    /**
     * @brief cancelButton click event
     * @details closes the window without saving the added information
     */
    void on_cancelButton_released();

private:
    Ui::AddSalePopup *ui;   /// @var pointer to window
    bool anotherSale;       /// @var anotherSale Indicates whether to add another sale for the member or not
    bool confirmSales;      /// @var confirmSales Indicates whether to confirm the current sales or not
};

#endif // ADDSALEPOPUP_H
