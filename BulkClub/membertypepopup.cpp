#include "membertypepopup.h"
#include "ui_membertypepopup.h"

MemberTypePopup::MemberTypePopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemberTypePopup)
{
    ui->setupUi(this);
}

MemberTypePopup::~MemberTypePopup()
{
    delete ui;
}
