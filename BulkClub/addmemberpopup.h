#ifndef ADDMEMBERPOPUP_H
#define ADDMEMBERPOPUP_H

#include <QDialog>

#include "helperLib.h"

namespace Ui {
class AddMemberPopup;
}

class AddMemberPopup : public QDialog
{
    Q_OBJECT

public:
    explicit AddMemberPopup(vector<Member> member, QWidget *parent = nullptr);
    ~AddMemberPopup();
    bool getConfirmAdd();
    bool getAddSale();

private slots:
    void on_confirmAddButton_released();

    void on_cancelAddButton_released();

    void on_addSaleButton_released();

private:
    Ui::AddMemberPopup *ui;
    bool confirmAdd; /// @var confirmAdd indicates whether to add the member shown or not
    bool addSale; /// @var addSale indicates whether to add a sale or not
};

#endif // ADDMEMBERPOPUP_H
