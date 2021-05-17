/**
 *  @file salespopup.h
 *  @brief Contains the definition of the SalesPopup window
 */

#ifndef SALESPOPUP_H
#define SALESPOPUP_H

#include "member.h"
#include "sale.h"
#include "helperLib.h"

#include <QDialog>

namespace Ui {
class SalesPopup;
}

/**
 * @class
 * @brief
 * @details
 */
class SalesPopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief
     * @details
     * @param
     * @param
     * @param
     */
    explicit SalesPopup(QString dateIndex, int idIndex, QWidget *parent = nullptr);
    /**
     * @brief
     * @details
     */
    ~SalesPopup();
    /**
     * @brief
     * @details
     * @param
     */
    vector<Member> getSaleMembers(Sale key);
    /**
     * @brief
     * @details
     * @param
     */
    void populateSaleCells(vector<Member> saleMembers);
    /**
     * @brief
     * @details
     * @param
     */
    void populateSummaryCells(vector<Member> saleMembers);
    /**
     * @brief
     * @details
     * @param
     * @param
     */
    QString indexToText(Member curMember, int columnIndex);
    /**
     * @brief
     * @details
     * @param
     */
    void updateTotal(vector<Member> saleMembers);

private slots:
    /**
     * @brief
     * @details
     * @param
     */
    void on_memTypeCombo_currentIndexChanged(int index);

private:
    Ui::SalesPopup *ui; ///@var
};

#endif // SALESPOPUP_H
