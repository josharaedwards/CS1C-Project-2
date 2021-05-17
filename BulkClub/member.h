/**
 *  @file member.h
 *  @brief Contains the definition of the Member Class
 */

#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QDate>
#include <vector>
#include "sale.h"
using namespace std;

const double REG_ANNUAL_DUE = 65.00;    /// @var regular membership annual due
const double EXEC_ANNUAL_DUE = 120.00;  /// @var executive membership annual due

/**
 *  @enum MemberStatus
 *  @brief represents the Member Status of the user
 */
enum MemberStatus {NEUTRAL, PROMOTED, DEMOTED};

/**
 * @class
 * @brief
 * @details
 */
class Member
{
    QString name;
    QDate expDate;

    int memberNum;
    double spentAmnt;
    double dueAmnt;
    double rebateAmnt;

    bool bIsExecutive;

    vector<Sale> sales;

public:
    //Constructors
    /**
     * @brief
     * @details
     */
    Member();
    /**
     * @brief
     * @details
     * @param
     * @param
     * @param
     * @param
     */
    Member(QString nameIn, QDate expDateIn, int memNumIn, bool execIn);
    /**
     * @brief
     * @details
     * @param
     * @param
     * @param
     * @param
     * @param
     */
    Member(QString nameIn, QDate expDateIn, int memNumIn, bool execIn, vector<Sale> salesIn);

    //Destructor
    /**
     * @brief
     * @details
     */
    ~Member();

    //Shallow & Deep Copy
    /**
     * @brief
     * @details
     * @param
     */
    Member(const Member& other);
    /**
     * @brief
     * @details
     * @param
     */
    void copy(Member other);

    //Overloaded Operators
    /**
     * @brief
     * @details
     * @param
     */
    Member operator+(const double amnt)
    {
        Member m(*this);

        m.spentAmnt += amnt;

        return m;
    }
    /**
     * @brief
     * @details
     * @param
     */
    Member operator-(const double amnt)
    {
        Member m(*this);

        m.spentAmnt -= amnt;

        return m;
    }

    //Helper Functions
    /**
     * @brief
     * @details
     * @param
     */
    void setName(QString nameIn);
    /**
     * @brief
     * @details
     * @param
     */
    void setExpDate(QDate expDateIn);
    /**
     * @brief
     * @details
     * @param
     */
    void setMemNum(int memNumIn);
    /**
     * @brief
     * @details
     * @param
     */
    void setDueAmnt(double dueAmntIn);
    /**
     * @brief
     * @details
     * @param
     */
    void setExec(bool execIn);
    /**
     * @brief
     * @details
     */
    void refreshSpentAmnt();
    /**
     * @brief
     * @details
     */
    void refreshRebateAmnt();
    /**
     * @brief
     * @details
     * @param
     */
    void addSale(Sale sale);
    /**
     * @brief
     * @details
     * @param
     */
    void addSales(vector<Sale> salesIn);
    /**
     * @brief
     * @details
     */
    QString getName();
    /**
     * @brief
     * @details
     */
    QDate getExpDate();
    /**
     * @brief
     * @details
     */
    int getMemNum();
    /**
     * @brief
     * @details
     */
    double getSpentAmnt();
    /**
     * @brief
     * @details
     */
    double getTaxAmnt();
    /**
     * @brief
     * @details
     */
    double getDueAmnt();
    /**
     * @brief
     * @details
     */
    double getRebateAmnt();
    /**
     * @brief
     * @details
     */
    bool IsExec();  
    /**
     * @brief
     * @details
     * @param
     */
    Sale getSale(int index);
    /**
     * @brief
     * @details
     * @param
     */
    vector<Sale> getSales();
    /**
     * @brief
     * @details
     * @param
     */
    bool hasSale(Sale saleIn);
    /**
     * @brief
     * @details
     */
    MemberStatus checkMemberStatus();
};

#endif // MEMBER_H
