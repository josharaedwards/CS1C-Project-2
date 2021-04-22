#ifndef HELPERLIB_H
#define HELPERLIB_H

#include <vector>
#include "member.h"
using namespace std;

enum SortType{NAME, EXP, NUM, SPENT_AMNT, REBATE_AMNT, EXEC};

//Search Functions

Member search(vector<Member> members, int memNumIn, bool& bSucceed);
Member search(vector<Member> members, QString nameIn, bool& bSucceed);

vector<Member> searchMult(vector<Member> members, bool execIn);
vector<Member> searchMult(vector<Member> members, QDate expDateIn);

//Sort Functions

vector<Member> sortBy(vector<Member> members, SortType sort);

void byName(vector<Member>& members);
void byExp(vector<Member>& members);
void byNum(vector<Member>& members);
void bySpentAmnt(vector<Member>& members);
void byRebateAmnt(vector<Member>& members);
void byExec(vector<Member>& members);

//Comparison Functions

bool isGreaterThan(QString first, QString second);
bool isGreaterThan(QDate first, QDate second);
bool isGreaterThan(double first, double second);
bool isGreaterThan(int first, int second);

#endif // HELPERLIB_H
