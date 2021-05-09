#ifndef ADDSALEPOPUP_H
#define ADDSALEPOPUP_H

#include <QDialog>
#include "helperLib.h"

namespace Ui {
class AddSalePopup;
}

class AddSalePopup : public QDialog
{
    Q_OBJECT

public:
    explicit AddSalePopup(Sale newSale, QWidget *parent = nullptr);
    ~AddSalePopup();
    bool getAnotherSale();
    bool getConfirmSales();
    static vector<Sale> addSales;

private slots:
    void on_addSaleButton_released();

    void on_confirmButton_released();

    void on_cancelButton_released();

private:
    Ui::AddSalePopup *ui;
    bool anotherSale; /// @var anotherSale Indicates whether to add another sale for the member or not
    bool confirmSales; /// @var confirmSales Indicates whether to confirm the current sales or not
};

#endif // ADDSALEPOPUP_H
