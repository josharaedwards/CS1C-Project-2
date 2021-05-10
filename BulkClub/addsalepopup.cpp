#include "addsalepopup.h"
#include "ui_addsalepopup.h"

vector<Sale> AddSalePopup::addSales;

AddSalePopup::AddSalePopup(Sale newSale, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSalePopup)
{
    ui->setupUi(this);

    /// @brief By default, anotherSale and confirmSale are set the false
    anotherSale = false;
    confirmSales = false;

    addSales.push_back(newSale);

    QAbstractItemModel *salesModel = createSalesModel(parent, addSales);
    ui->saleView->setModel(salesModel);
    ui->saleView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    double subtotal = 0.00;
    double tax = 0.00;
    double grandTotal = 0.00;

    /// @brief Iterating through the vector of sales to be added, calculating the subtotal
    for (unsigned int i = 0; i < addSales.size(); i++)
    {
        subtotal += addSales[i].getPrice() * addSales[i].getQuantity();
    }

    tax = subtotal * 0.0775;
    grandTotal = subtotal + tax;

    ui->subtotalLabel->setText("$" + QString::number(subtotal, 'f', 2));
    ui->taxLabel->setText("$" + QString::number(tax, 'f', 2));
    ui->totalLabel->setText("$" + QString::number(grandTotal, 'f', 2));

}

bool AddSalePopup::getAnotherSale()
{
    return anotherSale;
}

bool AddSalePopup::getConfirmSales()
{
    return confirmSales;
}

AddSalePopup::~AddSalePopup()
{
    delete ui;
}

void AddSalePopup::on_addSaleButton_released()
{
    anotherSale = true;
    this->accept();
}

void AddSalePopup::on_confirmButton_released()
{
    confirmSales = true;
    this->accept();
}

void AddSalePopup::on_cancelButton_released()
{
    this->accept();
}
