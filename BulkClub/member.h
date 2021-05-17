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
 * @class Member
 * @brief class representing a BulkClub member
 * @details used primarily in a vector of members, populated from a sql file
 */
class Member
{
    QString name;       /// @var QString name -Member name
    QDate expDate;      /// @var QDate expDate -Member expiration date
    int memberNum;      /// @var int memberNum -Member ID number
    double spentAmnt;   /// @var double spentAmnt -amount the Member has spent
    double dueAmnt;     /// @var double dueAmnt -amount the Member owes by the expiration date
    double rebateAmnt;  /// @var double rebateAmnt -size of the rebate the member will recieve
    bool bIsExecutive;  /// @var bool bIsExecutive -true if Member is an executive member
    vector<Sale> sales; /// @var vector of Sales objects representing all the purchases a member has made

public:
    //Constructors
    /**
     * @brief default Member contructor
     * @details populates data members with default values
     */
    Member();
    /**
     * @brief overloaded constructor 1
     * @details constructor for adding name, expiration date, member ID, and executive status
     * @param QString nameIn -passed in member name
     * @param QDate expDateIn -passed in member expiration date
     * @param int memNumIn -passed in member ID
     * @param bool execIn -pased in executive status
     */
    Member(QString nameIn, QDate expDateIn, int memNumIn, bool execIn);
    /**
     * @brief overloaded constructor 2
     * @details same as overloaded constructor 1, but also adds sales to the member
     * @param QString nameIn -passed in member name
     * @param QDate expDateIn -passed in member expiration date
     * @param int memNumIn -passed in member ID
     * @param bool execIn -pased in executive status
     * @param vector<Sale> salesIn -passed in sales vector for single member
     */
    Member(QString nameIn, QDate expDateIn, int memNumIn, bool execIn, vector<Sale> salesIn);

    //Destructor
    /**
     * @brief Member destructor
     * @details runs when program ends
     */
    ~Member();

    //Shallow & Deep Copy
    /**
     * @brief Member copy constructor
     * @details copies member from passed in Member to current member
     * @param Member& other -member to be copied
     */
    Member(const Member& other);
    /**
     * @brief copy member function
     * @details copies passed in Member to current member
     * @param Member other -member being passed in to copy
     */
    void copy(Member other);

    //Overloaded Operators
    /**
     * @brief overloaded + operator
     * @details adds passed in double to spent amount
     * @param double amnt -double representing amount spent to be added to Member
     */
    Member operator+(const double amnt)
    {
        Member m(*this);

        m.spentAmnt += amnt;

        return m;
    }
    /**
     * @brief overloaded - operator
     * @details subtracts passed in double from spent amount
     * @param double amnt -double representing amount of money to be subtracted from member
     */
    Member operator-(const double amnt)
    {
        Member m(*this);

        m.spentAmnt -= amnt;

        return m;
    }

    //Helper Functions
    /**
     * @brief setName function
     * @details function to set the name of a member
     * @param QString nameIn -passed in name to be assigned to member
     */
    void setName(QString nameIn);
    /**
     * @brief setExptDate function
     * @details function to set the expiration date of a member
     * @param QDate expDateIn -expiration date to be assigned to member
     */
    void setExpDate(QDate expDateIn);
    /**
     * @brief setMemNum function
     * @details function to set the member ID of a member
     * @param int memNumIn-member ID to be assigned to member
     */
    void setMemNum(int memNumIn);
    /**
     * @brief setDueAmnt function
     * @details function to set the due amount of a member
     * @param double dueAmntIn -due amount to be assigned to member
     */
    void setDueAmnt(double dueAmntIn);
    /**
     * @brief setExec function
     * @details function to set the executive status of a member
     * @param bool execIn -executive status to be assigned to a member
     */
    void setExec(bool execIn);
    /**
     * @brief refreshSpentAmnt function
     * @details recalculates the amount spent by a member
     */
    void refreshSpentAmnt();
    /**
     * @brief refreshRebateAmnt function
     * @details recalculates the rebate amount a member recieves
     */
    void refreshRebateAmnt();
    /**
     * @brief addSale function
     * @details function to add sale to a Member's Sales vector
     * @param Sale sale -sale to be added to a Member's Sales vector
     */
    void addSale(Sale sale);
    /**
     * @brief addSales function
     * @detailsfunction to add multiple sales to a Member's Sales vector
     * @param vector<Sale> salesIn -vector of Sales to be added to a Member's Sales vector
     */
    void addSales(vector<Sale> salesIn);
    /**
     * @brief getName function
     * @details returns the name of the member as a QString
     */
    QString getName();
    /**
     * @brief getExpDate function
     * @details returns the expiration date of a member as a QDate
     */
    QDate getExpDate();
    /**
     * @brief getMemNum function
     * @details returns the member ID of a Member as an int
     */
    int getMemNum();
    /**
     * @brief getSpentAmnt function
     * @details returns the amount spent by a member as a double
     */
    double getSpentAmnt();
    /**
     * @brief getTaxAmnt function
     * @details returns the amount of tax owed by a member as a double
     */
    double getTaxAmnt();
    /**
     * @brief getDueAmnt function
     * @details returns the membership dues of a member as a double
     */
    double getDueAmnt();
    /**
     * @brief getRebateAmnt function
     * @details returns the Rebate owed to the Member as a double
     */
    double getRebateAmnt();
    /**
     * @brief isExec function
     * @details returns true if the member is Executve
     */
    bool IsExec();  
    /**
     * @brief getSale function
     * @details returns the sale of a member at the passed in index
     * @param int index -index representing Member Sale to be accessed
     */
    Sale getSale(int index);
    /**
     * @brief getSales function
     * @details returns all the Sales attributed to the member as a vector
     */
    vector<Sale> getSales();
    /**
     * @brief hasSale function
     * @details returns true if a member has the Sale specified
     * @param Sale saleIn -Sale to find in a Member's Sales
     */
    bool hasSale(Sale saleIn);
    /**
     * @brief checkMemberStatus function
     * @details returns enum relating to whether or not the member should be promoted
     */
    MemberStatus checkMemberStatus();
};

#endif // MEMBER_H
