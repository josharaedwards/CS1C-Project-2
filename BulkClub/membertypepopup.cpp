#include "membertypepopup.h"
#include "ui_membertypepopup.h"

extern vector<Member> members;

MemberTypePopup::MemberTypePopup(loginStatus status, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemberTypePopup)
{
    ui->setupUi(this);

    if(status == ADMIN)
    {
        this->ui->execMemLabel->setHidden(false);
        this->ui->execMemTable->setHidden(false);
        this->ui->execNum->setHidden(false);
    }
    else
    {
        this->ui->execMemLabel->setHidden(true);
        this->ui->execMemTable->setHidden(true);
        this->ui->execNum->setHidden(true);
    }

    populateRegTable();

    if(status == ADMIN)
    {
        populateExecTable();
    }
}

void MemberTypePopup::populateRegTable()
{
    vector<Member> regMembers;
    int size = members.size();

    for(int i = 0; i < size; ++i)
    {
        if(members[i].checkMemberStatus() == PROMOTED)
        {
            regMembers.push_back(members[i]);
        }
    }

    int numOfEntries = regMembers.size();

    this->ui->regNum->setText(QString::number(numOfEntries));

    this->ui->regMemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->regMemTable->setRowCount(numOfEntries);

    for(int i = 0; i < numOfEntries; ++i)
    {
        QTableWidgetItem *item;

        for(int j = 0; j < 4; ++j)
        {
            item = new QTableWidgetItem;
            QString itemText = indexToText(regMembers[i], j);
            item->setText(itemText);

            this->ui->regMemTable->setItem(i, j, item);
        }
    }
}

void MemberTypePopup::populateExecTable()
{
    vector<Member> execMembers;
    int size = members.size();

    for(int i = 0; i < size; ++i)
    {
        if(members[i].checkMemberStatus() == DEMOTED)
        {
            execMembers.push_back(members[i]);
        }
    }

    int numOfEntries = execMembers.size();

    this->ui->execNum->setText(QString::number(numOfEntries));

    this->ui->execMemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->execMemTable->setRowCount(numOfEntries);

    for(int i = 0; i < numOfEntries; ++i)
    {
        QTableWidgetItem *item;

        for(int j = 0; j < 4; ++j)
        {
            item = new QTableWidgetItem;
            QString itemText = indexToText(execMembers[i], j);
            item->setText(itemText);

            this->ui->execMemTable->setItem(i, j, item);
        }
    }
}

QString MemberTypePopup::indexToText(Member member, int index)
{
    QString out;

    if(index == 0)
    {
        out = member.getName();
    }
    else if(index == 1)
    {
        out = QString::number(member.getMemNum());
    }
    else if(index == 2)
    {
        if(member.IsExec())
        {
            out = "Executive";
        }
        else
        {
            out = "Regular";
        }
    }
    else if (index == 3)
    {
        if(member.IsExec())
        {
            out = "DEMOTE";
        }
        else
        {
            out = "PROMOTE";
        }
    }
    else
    {
        out = "ERROR";
    }

    return out;
}

MemberTypePopup::~MemberTypePopup()
{
    delete ui;
}
