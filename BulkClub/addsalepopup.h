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
     * @brief
     * @details
     * @param
     */
    explicit AddSalePopup(Sale newSale, QWidget *parent = nullptr);
    /**
     * @brief
     * @details
     */
    ~AddSalePopup();
    /**
     * @brief
     * @details
     */
    bool getAnotherSale();
    /**
     * @brief
     * @details
     */
    bool getConfirmSales();
    /**
     * @brief
     * @details
     */
    static vector<Sale> addSales;

private slots:
    /**
     * @brief
     * @details
     */
    void on_addSaleButton_released();
    /**
     * @brief
     * @details
     */
    void on_confirmButton_released();
    /**
     * @brief
     * @details
     */
    void on_cancelButton_released();

private:
    Ui::AddSalePopup *ui; /// @var pointer to window
    bool anotherSale; /// @var anotherSale Indicates whether to add another sale for the member or not
    bool confirmSales; /// @var confirmSales Indicates whether to confirm the current sales or not
};

#endif // ADDSALEPOPUP_H
