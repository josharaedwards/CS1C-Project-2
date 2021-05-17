/**
 *  @file deletememberpopup.h
 *  @brief Contains the definition of the DeleteMemberPopup window
 */

#ifndef DELETEMEMBERPOPUP_H
#define DELETEMEMBERPOPUP_H

#include <QDialog>
#include <QAbstractItemModel>

#include "member.h"
#include "helperLib.h"

namespace Ui {
class DeleteMemberPopup;
}

class DeleteMemberPopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief
     * @details
     * @param
     * @param
     */
    explicit DeleteMemberPopup(vector<Member> member, QWidget *parent = nullptr);
    /**
     * @brief
     * @details
     */
    ~DeleteMemberPopup();
    /**
     * @brief
     * @details
     */
    bool getConfirmDelete();

private slots:
    /**
     * @brief
     * @details
     */
    void on_deleteButton_released();
    /**
     * @brief
     * @details
     */
    void on_cancelButton_released();

private:
    Ui::DeleteMemberPopup *ui;  /// @var pointer to DeleteMemberPopup window
    bool confirmDelete;         /// @var confirmDelete indicates whether to delete the member shown or not
};

#endif // DELETEMEMBERPOPUP_H
