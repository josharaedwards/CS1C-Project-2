#ifndef MEMBERTYPEPOPUP_H
#define MEMBERTYPEPOPUP_H

#include <QDialog>

namespace Ui {
class MemberTypePopup;
}

class MemberTypePopup : public QDialog
{
    Q_OBJECT

public:
    explicit MemberTypePopup(QWidget *parent = nullptr);
    ~MemberTypePopup();

private:
    Ui::MemberTypePopup *ui;
};

#endif // MEMBERTYPEPOPUP_H
