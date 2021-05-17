/**
 * @file addmemberpopup.h
 * @brief contains definition of AddMemberPopup window
 */

#ifndef ADDMEMBERPOPUP_H
#define ADDMEMBERPOPUP_H

#include <QDialog>

#include "helperLib.h"

namespace Ui {
class AddMemberPopup;
}

/**
 * @class AddMemberPopup
 * @brief Appears when an Administrator presses Confirm after entering information
 * to add a new member to the Bulk Club
 */
class AddMemberPopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief AddMemberPopup Constructor
     * @param member Vector containing the member the Admin just entered the information for
     * @param QWidget* Parent widget
     */
    explicit AddMemberPopup(vector<Member> member, QWidget *parent = nullptr);

    /**
     * @brief The AddMemberPopup Destructor
     */
    ~AddMemberPopup();

    /**
     * @brief getConfirmAdd
     *
     * Returns true if the Admin pressed either Add Sale or Confirm of the Dialog, otherwise
     * returns false in the case that Cancel was pressed.
     * @return confirmAdd, a member variable
     */
    bool getConfirmAdd();

    /**
     * @brief getAddSale
     *
     * Returns true if the Add Sale button was pressed, otherwise returns false if
     * @return addSale, a membervariable
     */
    bool getAddSale();

private slots:
    /**
     * @brief on_confirmAddButton_released
     *
     * The Confirm button of the Dialog was pressed
     */
    void on_confirmAddButton_released();

    /**
     * @brief on_cancelAddButton_released
     *
     * The Cancel button of the Dialog was pressed
     */
    void on_cancelAddButton_released();

    /**
     * @brief on_addSaleButton_released
     *
     * The Add Sale button of the Dialog was pressed
     */
    void on_addSaleButton_released();

private:
    Ui::AddMemberPopup *ui; /// @var ui contains all variables handled by the ui form
    bool confirmAdd; /// @var confirmAdd indicates whether to add the member shown or not
    bool addSale; /// @var addSale indicates whether to add a sale or not
};

#endif // ADDMEMBERPOPUP_H
