#ifndef HELPERLIB_H
#define HELPERLIB_H

#include <iostream>
#include <vector>
#include <QStandardItemModel>
#include "member.h"
#include "inventory.h"
#include "dbmanager.h"
using namespace std;

enum SortType{NAME, EXP, NUM, SPENT_AMNT, REBATE_AMNT};

//Search Functions

Member search(vector<Member> members, int memNumIn, bool& bSucceed);
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

QAbstractItemModel* createInventoryModel(QWidget* parent, vector<Inventory> inventory);
void addInventory(QAbstractItemModel* model, Inventory invIn);

void deleteMember(vector<Member>& members, int memNumIn);

#endif // HELPERLIB_H
