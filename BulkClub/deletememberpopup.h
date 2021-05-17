#ifndef DELETEMEMBERPOPUP_H
#define DELETEMEMBERPOPUP_H

#include <QDialog>
#include <QAbstractItemModel>

#include "member.h"
#include "helperLib.h"

namespace Ui {
class DeleteMemberPopup;
}

/**
 * @class DeleteMemberPopup
 *
 * @brief A class inheriting from QDialog to facilitate
 * deleting a member from the database
 */
class DeleteMemberPopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief DeleteMemberPopup Constructor
     * @param member Vector containing the member the Admin just entered the information for
     * @param parent Parent widget
     */
    explicit DeleteMemberPopup(vector<Member> member, QWidget *parent = nullptr);
    /**
     * @brief The DeleteMemberPopup Destructor
     */
    ~DeleteMemberPopup();
    /**
     * @brief getConfirmDelete
     *
     * Returns true if the Admin pressed either Add Sale or Confirm of the Dialog, otherwise
     * returns false in the case that Cancel was pressed.
     * @return confirmDelete, a member variable
     */
    bool getConfirmDelete();

private slots:
    /**
     * @brief this slot sets confirmDelete to true and then
     * calls accept()
     */
    void on_deleteButton_released();

    /**
     * @brief this slot sets confirmDelete to false and then
     * calls accept()
     */
    void on_cancelButton_released();

private:
    ///@var pointer to access this popup's ui
    Ui::DeleteMemberPopup *ui;
    ///@var confirmDelete indicates whether to delete the member shown or not
    bool confirmDelete;
};

#endif // DELETEMEMBERPOPUP_H
