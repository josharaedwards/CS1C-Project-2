#include "addinvpopup.h"
#include "ui_addinvpopup.h"

AddInvPopup::AddInvPopup(Inventory newItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddInvPopup)
{
    ui->setupUi(this);

    newItem.setName(ui->lineEditName->text());
    newItem.setPrice(ui->lineEditPrice->text().toDouble());
    newItem.setQuantity(ui->lineEditQuantity->text().toDouble());
    newItem.refreshTotal();
}

AddInvPopup::~AddInvPopup()
{
    delete ui;
}

void AddInvPopup::on_buttonSubmit_released()
{
    this->accept();
}
