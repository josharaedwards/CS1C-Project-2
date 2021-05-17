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

vector<Member> searchMult(vector<Member> members, bool execIn);
vector<Member> searchMult(vector<Member> members, QDate expDateIn);

//Sort Functions

vector<Member> sort(vector<Member> members, SortType sortBy);

void sortByName(vector<Member>& members);
void sortByExp(vector<Member>& members);
void sortByNum(vector<Member>& members);
void sortBySpentAmnt(vector<Member>& members);
void sortByRebateAmnt(vector<Member>& members);
void sortByExec(vector<Member>& members);

//Filter Functions

vector<Member> filterBy(vector<Member> members, SortType sort, bool isInclusive = false);

//Comparison Functions

bool isGreaterThan(QString first, QString second);
bool isGreaterThan(QDate first, QDate second);
bool isGreaterThan(double first, double second);
bool isGreaterThan(int first, int second);

//Relational Functions

void saleToMembers(vector<Member>& members, Sale sale);
void salesToMembers(vector<Member>& members, vector<Sale> sales);

QAbstractItemModel* createMemberModel(QWidget* parent, vector<Member> members);
void addMember(QAbstractItemModel* model, Member memIn);

QAbstractItemModel* createSalesModel(QWidget* parent, vector<Sale> sales);
void addSale(QAbstractItemModel* model, Sale saleIn);

void addInventory(QAbstractItemModel* model, Inventory invIn);
void addInventory(QAbstractItemModel* model, vector<Inventory> invIn);

void deleteMember(vector<Member>& members, int memNumIn);

#endif // HELPERLIB_H
