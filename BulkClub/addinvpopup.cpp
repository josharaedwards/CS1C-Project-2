#include "addinvpopup.h"
#include "ui_addinvpopup.h"

AddInvPopup::AddInvPopup(Inventory newItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddInvPopup)
{
    ui->setupUi(this);
}

AddInvPopup::~AddInvPopup()
{
    delete ui;
}
