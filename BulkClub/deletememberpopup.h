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
    explicit DeleteMemberPopup(vector<Member> member, QWidget *parent = nullptr);
    ~DeleteMemberPopup();
    bool getConfirmDelete();

private slots:
    void on_deleteButton_released();

    void on_cancelButton_released();

private:
    Ui::DeleteMemberPopup *ui;
    bool confirmDelete; /// @var confirmDelete indicates whether to delete the member shown or not
};

#endif // DELETEMEMBERPOPUP_H
