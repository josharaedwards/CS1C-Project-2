#include "addmemberpopup.h"
#include "ui_addmemberpopup.h"

AddMemberPopup::AddMemberPopup(vector<Member> member, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMemberPopup)
{
    ui->setupUi(this);

    addSale = false;

    QAbstractItemModel *memberModel = createMemberModel(parent, member);
    ui->addMemView->setModel(memberModel);
    ui->addMemView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

AddMemberPopup::~AddMemberPopup()
{
    delete ui;
}

/// @brief Returns whether to add the shown member or not
bool AddMemberPopup::getConfirmAdd()
{
    return confirmAdd;
}

/// @brief Returns whether to add a sale to the shown member or not
bool AddMemberPopup::getAddSale()
{
    return addSale;
}

/// @brief The user confirmed adding the member to the Bulk Club
void AddMemberPopup::on_confirmAddButton_released()
{
    confirmAdd = true;
    this->accept();
}

/// @brief The user indicated not to add the member to the Bulk Club
void AddMemberPopup::on_cancelAddButton_released()
{
    confirmAdd = false;
    this->accept();
}

/// @brief The user indicated they want to add a sale for the member
void AddMemberPopup::on_addSaleButton_released()
{
    confirmAdd = true;
    addSale = true;
    this->accept();
}
