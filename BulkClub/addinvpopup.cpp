#include "addinvpopup.h"
#include "ui_addinvpopup.h"
#include "dbmanager.h"

extern vector<Inventory> inventory;

AddInvPopup::AddInvPopup(Inventory newItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddInvPopup)
{
    ui->setupUi(this);



    //inventory.push_back(newItem);
}

AddInvPopup::~AddInvPopup()
{
    delete ui;
}

void AddInvPopup::on_buttonSubmit_released()
{
    Inventory newItem;
    newItem.setName(ui->lineEditName->text());
    newItem.setPrice(ui->lineEditPrice->text().toDouble());
    newItem.setQuantity(ui->lineEditQuantity->text().toInt());
    newItem.refreshTotal();
    inventory.push_back(newItem);

    DbManager d;
    d.saveInventoryTable();
    this->accept();

    cout << "Inventory after adding item: " << endl;
    int vecSize = inventory.size();
    for(int i = 0; i < vecSize; i++)
    {
        cout << "inventory[" << i << "]: " << inventory[i].getName().toStdString() << " " << inventory[i].getPrice()
             << " " << inventory[i].getQuantity() << " " << inventory[i].getTotal() << endl;
    }
}
