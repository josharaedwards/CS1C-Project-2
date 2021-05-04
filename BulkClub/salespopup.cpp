#include "salespopup.h"
#include "ui_salespopup.h"

extern vector<Member> members;
extern vector<Sale> sales;

vector<Member> saleMembers;
vector<Member> saleMembersExec;
vector<Member> saleMembersReg;

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
    saleMembers = getSaleMembers(key);

    saleMembersExec = searchMult(saleMembers, true);
    saleMembersReg = searchMult(saleMembers, false);

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
                vector<Sale> tempSale;
                tempSale.push_back(curSale);

                Member tempMember(members[j].getName(), members[j].getExpDate(), members[j].getMemNum(), members[j].IsExec(), tempSale);

                saleMembers.push_back(tempMember);
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
            QString itemText = indexToText(saleMembers[i], j);
            item->setText(itemText);

            this->ui->salesMemberInfo->setItem(i, j, item);
        }
    }
}

void SalesPopup::populateSummaryCells(vector<Member> saleMembers)
{
    int numOfEntries = saleMembers.size();
    int numfOfExecs = 0;
    int numOfReg = 0;
    double total = 0.00;

    for(int i = 0; i < numOfEntries; ++i)
    {
        total += saleMembers[i].getSpentAmnt();

        if(saleMembers[i].IsExec())
        {
            numfOfExecs++;
        }
        else
        {
            numOfReg++;
        }
    }

    QTableWidgetItem *item;
    QString itemText;

    item = new QTableWidgetItem;
    itemText = QString{"$%1"}.arg(total, 4, 'f', 2, '0');
    item->setText(itemText);
    this->ui->salesTotalInfo->setItem(0, 0, item);

    item = new QTableWidgetItem;
    itemText = QString::number(numfOfExecs);
    item->setText(itemText);
    this->ui->salesTotalInfo->setItem(0, 1, item);

    item = new QTableWidgetItem;
    itemText = QString::number(numOfReg);
    item->setText(itemText);
    this->ui->salesTotalInfo->setItem(0, 2, item);
}

QString SalesPopup::indexToText(Member curMember, int columnIndex)
{
    QString outTxt = "None";
    Sale tempSale = curMember.getSale(0);

    switch(columnIndex)
    {
    case 0: //Name
        outTxt = curMember.getName();
        break;
    case 1: //MemberType
        if(curMember.IsExec())
        {
            outTxt = "Executive";
        }
        else
        {
            outTxt = "Regular";
        }
        break;
    case 2: //Sale Item
        outTxt = tempSale.getName();
        break;
    case 3: //Sale Quantity
        outTxt = QString::number(tempSale.getQuantity());
        break;
    case 4: //Sale Total
        outTxt = QString{"$%1"}.arg(curMember.getSpentAmnt(), 4, 'f', 2, '0');
        break;
    default:
        outTxt = "ERROR";
    }

    return outTxt;
}

void SalesPopup::updateTotal(vector<Member> saleMembers)
{
    int numOfEntries = saleMembers.size();
    double total = 0.00;

    for(int i = 0; i < numOfEntries; ++i)
    {
        total += saleMembers[i].getSpentAmnt();
    }

    QTableWidgetItem *item;
    QString itemText;

    item = new QTableWidgetItem;
    itemText = QString{"$%1"}.arg(total, 4, 'f', 2, '0');
    item->setText(itemText);
    this->ui->salesTotalInfo->setItem(0, 0, item);
}

void SalesPopup::on_memTypeCombo_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        populateSaleCells(saleMembers);
        updateTotal(saleMembers);
        break;
    case 1:
        populateSaleCells(saleMembersExec);
        updateTotal(saleMembersExec);
        break;
    case 2:
        populateSaleCells(saleMembersReg);
        updateTotal(saleMembersReg);
        break;
    default:
        populateSaleCells(saleMembers);
        updateTotal(saleMembers);
    }
}
