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

private:
    Ui::SalesPopup *ui;
};

#endif // SALESPOPUP_H
