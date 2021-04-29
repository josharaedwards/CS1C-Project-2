#include "salespopup.h"
#include "ui_salespopup.h"

extern vector<Member> members;
extern vector<Sale> sales;

SalesPopup::SalesPopup(QString dateIndex, int idIndex, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalesPopup)
{
    ui->setupUi(this);

    this->ui->salesDate->setText(dateIndex);

    QDate saleDate = QDate::fromString(dateIndex, "M/d/yyyy");

    Sale key;
    key.setDate(saleDate);
    key.setMemNum(idIndex);
    vector<Member> saleMembers = getSaleMembers(key);

    //Populate Info Table
    populateSaleCells(saleMembers);

    //Populate Summary Table
    populateSummaryCells(saleMembers);
}

SalesPopup::~SalesPopup()
{
    delete ui;
}

vector<Member> SalesPopup::getSaleMembers(Sale key)
{
    vector<Member> saleMembers;
    vector<Sale> tempSales;
    int saleSize = sales.size();
    int memSize = members.size();

    for(int i = 0; i < saleSize; ++i)
    {
        if(sales[i].getDate() == key.getDate())
        {
            tempSales.push_back(sales[i]);
        }
    }

    //Get Members From Sales
    int tempSize = tempSales.size();

    for(int i = 0; i < tempSize; ++i)
    {
        Sale curSale = tempSales[i];

        for(int j = 0; j < memSize; ++j)
        {
            if(members[j].hasSale(curSale))
            {
                saleMembers.push_back(members[j]);
            }
        }
    }

    return saleMembers;
}

void SalesPopup::populateSaleCells(vector<Member> saleMembers)
{
    int numOfEntries = saleMembers.size();

    this->ui->salesMemberInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->salesMemberInfo->setRowCount(numOfEntries);

    for(int i = 0; i < numOfEntries; ++i)
    {
        QTableWidgetItem *item;

        for(int j = 0; j < 5; ++j)
        {
            item = new QTableWidgetItem;
            QString itemText = "None"; //add functionality to convert i and j into text
            item->setText(itemText);

            this->ui->salesMemberInfo->setItem(i, j, item);
        }
    }
}

void SalesPopup::populateSummaryCells(vector<Member> saleMembers)
{

}
