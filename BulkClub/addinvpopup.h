/**
 * @file addinvpopup.h
 * @brief contains definition of AddInvPopup window
 */

#ifndef ADDINVPOPUP_H
#define ADDINVPOPUP_H

#include <QDialog>
#include "inventory.h"

namespace Ui {
class AddInvPopup;
}

/**
 * @class AddInvPopup
 * @brief Appears when an user wants to add an inventory item.
 */
class AddInvPopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief constructor for AddInvPopup window
     * @param Inventory - passes inventory object representing item to be added
     * @param QWidget* - QWidget parent object QItem
     */
    explicit AddInvPopup(Inventory newItem, QWidget *parent = nullptr);
    ~AddInvPopup();

private slots:
    /**
     * @brief submit button pressed event
     * @details when submit button is pressed, the window closes and the inventory table updates
     */
    void on_buttonSubmit_released();

private:
    Ui::AddInvPopup *ui;    /// @var AddInvPopup *ui pointer to window object
};

#endif // ADDINVPOPUP_H
