#ifndef SALESPOPUP_H
#define SALESPOPUP_H

#include <QDialog>

namespace Ui {
class SalesPopup;
}

class SalesPopup : public QDialog
{
    Q_OBJECT

public:
    explicit SalesPopup(QWidget *parent = nullptr);
    ~SalesPopup();

private:
    Ui::SalesPopup *ui;
};

#endif // SALESPOPUP_H
