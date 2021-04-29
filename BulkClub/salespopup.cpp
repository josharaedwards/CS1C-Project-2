#include "salespopup.h"
#include "ui_salespopup.h"

SalesPopup::SalesPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalesPopup)
{
    ui->setupUi(this);
}

SalesPopup::~SalesPopup()
{
    delete ui;
}
