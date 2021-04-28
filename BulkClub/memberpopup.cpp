#include "memberpopup.h"
#include "ui_memberpopup.h"

memberPopup::memberPopup(QString memberID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::memberPopup)
{
    ui->setupUi(this);

    // Add customer name to the label maybe?
    this->ui->memberIDLabel->setText(memberID);

    //fix connection
    memberModel = connection.createMemberTable();
    memberProxyModel = new QSortFilterProxyModel(this);
    memberProxyModel->setSourceModel(memberModel);
    memberView = this->ui->memberInfoTable;
    memberView->setModel(memberProxyModel);
    this->memberProxyModel->setFilterRegularExpression(memberID);

    /// @brief Formats the column sizes by allowing them to stretch
    memberView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //fix connection
    salesModel = connection.createSalesTable();
    salesProxyModel = new QSortFilterProxyModel(this);
    salesProxyModel->setSourceModel(salesModel);
    salesView = this->ui->purchaseInfoTable;
    salesView->setModel(salesProxyModel);
    this->salesProxyModel->setFilterRegularExpression(memberID);

    /// @brief Formats the column sizes by allowing them to stretch
    salesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->setVisible(false);
}

memberPopup::~memberPopup()
{
    delete ui;
}
