#ifndef MEMBERTYPEPOPUP_H
#define MEMBERTYPEPOPUP_H

#include <QDialog>
#include "authenticate.h"
#include "member.h"

namespace Ui {
class MemberTypePopup;
}

class MemberTypePopup : public QDialog
{
    Q_OBJECT

public:
    explicit MemberTypePopup(loginStatus status, QWidget *parent = nullptr);
    ~MemberTypePopup();

    void populateRegTable();
    void populateExecTable();

    QString indexToText(Member member, int index);

private:
    Ui::MemberTypePopup *ui;
};

#endif // MEMBERTYPEPOPUP_H
