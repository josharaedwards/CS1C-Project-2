#include "addinvpopup.h"
#include "ui_addinvpopup.h"
#include "dbmanager.h"
#include "helperLib.h"

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
    DbManager d;
    Inventory newItem;
    int quantityIndex;
    int tempQuantity;
    newItem.setName(ui->lineEditName->text());
    newItem.setPrice(ui->lineEditPrice->text().toDouble());
    newItem.setQuantity(ui->lineEditQuantity->text().toInt());
    newItem.refreshTotal();


    if(d.isInInventory(newItem.getName()))
    {
        quantityIndex = d.findInvIndex(newItem.getName());
        tempQuantity = inventory[quantityIndex].getQuantity() + newItem.getQuantity();
        inventory[quantityIndex].setQuantity(tempQuantity);
        inventory[quantityIndex].refreshTotal();
        newItem.setPrice(inventory[quantityIndex].getPrice());
    }
    else
    {
        inventory.push_back(newItem);
    }


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
