#include "memberpopup.h"
#include "ui_memberpopup.h"

extern vector<Member> memVec;
extern vector<Sale> saleVec;

memberPopup::memberPopup(QString memberID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::memberPopup)
{
    ui->setupUi(this);

    // Add customer name to the label maybe?
    int index = 0;
    for(int i = 0; i <= memVec.size(); i++){
        if(memberID == QString::number(memVec[i].getMemNum())){
            this->ui->memberIDLabel->setText(memVec[i].getName());
            index = i;
            break;
        }
    }

    createMemTable(index);
    createSaleTable(index);
    this->setVisible(false);
}

memberPopup::~memberPopup()
{
    delete ui;
}

void memberPopup::createMemTable(int index){
    QTableWidgetItem* memItem;
    QTableWidget* memT;

    memT = this->ui->memTable;

    memT->setEditTriggers(QAbstractItemView::NoEditTriggers);

    memT->setRowCount(1);                 //1 row for 1 member
    memT->setColumnCount(4);              //4 colums, 1 for each Member field

    QStringList hLabels;
    hLabels << "Name" << "Member ID" << "Membership" << "Exp Date";
    memT->setHorizontalHeaderLabels(hLabels);

    for(int j = 0; j < memT->columnCount(); j++){
        memItem = new QTableWidgetItem;
        switch(j){
            case 0: memItem->setText(memVec[index].getName());                          break;
            case 1: memItem->setText(QString::number(memVec[index].getMemNum()));       break;
            case 2: if(memVec[index].IsExec()){
                        memItem->setText("Executive");
                    } else {
                        memItem->setText("Regular");
                    }
                                                                                        break;
            case 3: memItem->setText(memVec[index].getExpDate().toString("MM/dd/yyyy"));break;
        }
        memT->setItem(0, j, memItem);
    }
    memT->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    memT->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    memT->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    memT->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

void memberPopup::createSaleTable(int index){
    QTableWidgetItem* saleItem;
    QTableWidget* saleT;

    vector<Sale> memSales = memVec[index].getSales();


    saleT = this->ui->saleTable;

    saleT->setEditTriggers(QAbstractItemView::NoEditTriggers);


    saleT->setRowCount(memSales.size());   //matches number of rows in vector of Member Objects
    saleT->setColumnCount(5);              //4 colums, 1 for each Member field
    QStringList hLabels;
    hLabels << "Date" << "Member ID" << "Product" << "Price" << "Quantity";
    saleT->setHorizontalHeaderLabels(hLabels);

    for(int i = 0; i < saleT->rowCount(); i++){
        for(int j = 0; j < saleT->columnCount(); j++){
            saleItem = new QTableWidgetItem;
            switch(j){
                case 0: saleItem->setText(memSales[i].getDate().toString("MM/dd/yyyy"));     break;
                case 1: saleItem->setText(QString::number(memSales[i].getMemNum())); break;
                case 2: saleItem->setText(memSales[i].getName());    break;
                case 3: saleItem->setText(QString::number(memSales[i].getPrice())); break;
                case 4: saleItem->setText(QString::number(memSales[i].getQuantity())); break;
            }
            saleT->setItem(i, j, saleItem);
        }
    }
    saleT->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    saleT->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    saleT->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    saleT->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    saleT->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
}
