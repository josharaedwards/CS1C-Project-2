#include "deletememberpopup.h"
#include "ui_deletememberpopup.h"

DeleteMemberPopup::DeleteMemberPopup(vector<Member> member, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteMemberPopup)
{
    ui->setupUi(this);

    QAbstractItemModel *memberModel = createMemberModel(parent, member);
    ui->deleteMemView->setModel(memberModel);
    ui->deleteMemView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

DeleteMemberPopup::~DeleteMemberPopup()
{
    delete ui;
}

/// @brief Returns whether the user wants to delete the member or not
bool DeleteMemberPopup::getConfirmDelete()
{
    return confirmDelete;
}

/// @brief The user confirmed they want to delete the member shown
void DeleteMemberPopup::on_deleteButton_released()
{
    confirmDelete = true;
    this->accept();
}

/// @brief The user indicated they did not want to delete the member shown
void DeleteMemberPopup::on_cancelButton_released()
{
    confirmDelete = false;
    this->accept();
}
