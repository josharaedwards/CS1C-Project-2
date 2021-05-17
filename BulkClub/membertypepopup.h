/**
 *  @file membertypepopup.h
 *  @brief Contains the definition of the MemberTypePopup Class
 */

#ifndef MEMBERTYPEPOPUP_H
#define MEMBERTYPEPOPUP_H

#include <QDialog>
#include "authenticate.h"
#include "member.h"

namespace Ui {
class MemberTypePopup;
}

/**
 * @class
 * @brief
 * @details
 */
class MemberTypePopup : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief
     * @details
     * @param
     * @param
     */
    explicit MemberTypePopup(loginStatus status, QWidget *parent = nullptr);
    /**
     * @brief
     * @details
     */
    ~MemberTypePopup();
    /**
     * @brief
     * @details
     */
    void populateRegTable();
    /**
     * @brief
     * @details
     */
    void populateExecTable();
    /**
     * @brief
     * @details
     * @param
     * @param
     */
    QString indexToText(Member member, int index);

private:
    Ui::MemberTypePopup *ui;    ///@var
};

#endif // MEMBERTYPEPOPUP_H
