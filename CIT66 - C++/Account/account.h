//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This is the custom class Account.
//
// Usage:        #include "account.h"
//
//---------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <string>

using namespace std;

class Account {
private:
	int accountNumber;
	string ownerName;
	double balance;
protected:
	string getOwnerName();
	int getAccountNumber();
	void setOwnerName(string);
	void setAccountNumber(int);
	double getBalance();
	void credit(double);
	void debit(double);
public:
	Account();
	Account(int, string);
};

Account::Account() {
	accountNumber = 000;
	ownerName = "Moetron";
	balance = 0.00;
}

Account::Account(int num, string name) {
	accountNumber = num;
	ownerName = name;
	balance = 0.00;
}

string Account::getOwnerName() {
	return ownerName;
}

int Account::getAccountNumber() {
	return accountNumber;
}

void Account::setOwnerName(string new_name) {
	ownerName = new_name;
}

void Account::setAccountNumber(int new_num) {
	accountNumber = new_num;
}

double Account::getBalance() {
	return balance;
}

void Account::credit(double deposit) {
	balance += deposit;
}

void Account::debit(double charge) {
	balance -= charge;
}
