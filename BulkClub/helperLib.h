/**
 *  @file helperLib.h
 *  @brief Contains prototypes of various helper functions
 */

#ifndef HELPERLIB_H
#define HELPERLIB_H

#include <iostream>
#include <vector>
#include <QStandardItemModel>
#include "member.h"
#include "inventory.h"
#include "dbmanager.h"
using namespace std;
/**
 * @brief enum to facilitate retrieving the appropriate column index
 * when sorting
 */
enum SortType{NAME, EXP, NUM, SPENT_AMNT, REBATE_AMNT};

//Search Functions
/**
* @brief search function to search a vector of members
* by member number
* @param members a vector of type Member
* @param memNumIn the integer value to search by
* @param bSucceed a boolean to indicate success/failure
* @return m the Member object that was copied from the passed vector
* if the member number was found
*/
Member search(vector<Member> members, int memNumIn, bool& bSucceed);

/**
* @brief search function to search a vector of members
* by member name
* @param members a vector of type Member
* @param nameIn QString value to search by
* @param bSucceed a boolean to indicate success/failure
* @return m the Member object that was copied from the passed vector
* if the member name was found
*/
Member search(vector<Member> members, QString nameIn, bool& bSucceed);

/**
* @brief search function to search a vector of members
* by member executive status. Finds all members with
* matching exective status
* @param members a vector of type Member
* @param execIn bool value to search by
* @return memsOut the Member vector containing all
* members that matched the exec type
*/
vector<Member> searchMult(vector<Member> members, bool execIn);

/**
* @brief search function to search a vector of members
* by expiration date. Finds all members with
* matching expiration dates.
* @param members a vector of type Member
* @param expDateIn QDate value to search by
* @return memsOut the Member vector containing all
* members that matched the searched date
*/
vector<Member> searchMult(vector<Member> members, QDate expDateIn);

//Sort Functions

/**
* @brief sort function to rearrange the elements of
* a member vector based on the specified enum
* @param members a vector of type Member
* @param SortType enum to determine which element
* to sort by
* @return memsOut the Member vector sorted by the passed
* sorting case
*/
vector<Member> sort(vector<Member> members, SortType sortBy);

/**
* @brief sort function to sort a vector of members
* by their names
* @param members a vector of type Member
*/
void sortByName(vector<Member>& members);
/**
* @brief sort function to sort a vector of members
* by their expiration dates
* @param members a vector of type Member
*/
void sortByExp(vector<Member>& members);
/**
* @brief sort function to sort a vector of members
* by their membership IDs
* @param members a vector of type Member
*/
void sortByNum(vector<Member>& members);
/**
* @brief sort function to sort a vector of members
* by their spent amount
* @param members a vector of type Member
*/
void sortBySpentAmnt(vector<Member>& members);
/**
* @brief sort function to sort a vector of members
* by their rebate amount
* @param members a vector of type Member
*/
void sortByRebateAmnt(vector<Member>& members);
/**
* @brief sort function to sort a vector of members
* by their executive status
* @param members a vector of type Member
*/
void sortByExec(vector<Member>& members);

//Filter Functions

vector<Member> filterBy(vector<Member> members, SortType sort, bool isInclusive = false);

//Comparison Functions

/**
* @brief compares two QStrings and returns true or false
* depending on the comparison
* @param first first QString in the comparison
* @param second second QString in the comparison
* @return returns true if first > second else false
*/
bool isGreaterThan(QString first, QString second);

/**
* @brief compares two QDates and returns true or false
* depending on the comparison
* @param first first QDate in the comparison
* @param second second QDate in the comparison
* @return returns true if first > second else false
*/
bool isGreaterThan(QDate first, QDate second);

/**
* @brief compares two doubles and returns true or false
* depending on the comparison
* @param first first double in the comparison
* @param second second double in the comparison
* @return returns true if first > second else false
*/
bool isGreaterThan(double first, double second);

/**
* @brief compares two ints and returns true or false
* depending on the comparison
* @param first first int in the comparison
* @param second second int in the comparison
* @return returns true if first > second else false
*/
bool isGreaterThan(int first, int second);

//Relational Functions
/**
* @brief takes a vector of Members and an instance of
* a Sale object and appends the sale information to the
* appropriate member
* @param members vector of Members to search through
* @param sale object of Sale to be appended to the
* appropriate member
*/
void saleToMembers(vector<Member>& members, Sale sale);

/**
* @brief takes a vector of Members and a vector
* of Sales and appends the sale information to the
* appropriate member
* @param members vector of Members to search through
* @param sales vector of Sales to be added to the
* appropriate objects of type Member
*/
void salesToMembers(vector<Member>& members, vector<Sale> sales);

QAbstractItemModel* createMemberModel(QWidget* parent, vector<Member> members);
void addMember(QAbstractItemModel* model, Member memIn);

QAbstractItemModel* createSalesModel(QWidget* parent, vector<Sale> sales);
void addSale(QAbstractItemModel* model, Sale saleIn);

void addInventory(QAbstractItemModel* model, Inventory invIn);
void addInventory(QAbstractItemModel* model, vector<Inventory> invIn);

void deleteMember(vector<Member>& members, int memNumIn);

#endif // HELPERLIB_H
