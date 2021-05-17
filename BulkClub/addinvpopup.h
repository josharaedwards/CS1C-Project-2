#ifndef ADDINVPOPUP_H
#define ADDINVPOPUP_H

#include <QDialog>
#include "inventory.h"

namespace Ui {
class AddInvPopup;
}

class AddInvPopup : public QDialog
{
    Q_OBJECT

public:
    explicit AddInvPopup(Inventory newItem, QWidget *parent = nullptr);
    ~AddInvPopup();

private slots:
    void on_buttonSubmit_released();

private:
    Ui::AddInvPopup *ui;
};

#endif // ADDINVPOPUP_H
