#ifndef SALESPOPUP_H
#define SALESPOPUP_H

#include "member.h"
#include "sale.h"
#include "helperLib.h"

#include <QDialog>

namespace Ui {
class SalesPopup;
}

class SalesPopup : public QDialog
{
    Q_OBJECT

public:
    explicit SalesPopup(QString dateIndex, int idIndex, QWidget *parent = nullptr);
    ~SalesPopup();

    vector<Member> getSaleMembers(Sale key);

    void populateSaleCells(vector<Member> saleMembers);
    void populateSummaryCells(vector<Member> saleMembers);

    QString indexToText(Member curMember, int columnIndex);
    void updateTotal(vector<Member> saleMembers);

private slots:
    void on_memTypeCombo_currentIndexChanged(int index);

private:
    Ui::SalesPopup *ui;
};

#endif // SALESPOPUP_H
