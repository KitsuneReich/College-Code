//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This is the subclass checkingAccount. Note: PayCheck() also has an
//               overdraft charge of $30.
//
// Usage:        #include "checking.h"
//
//---------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <string>
#include "account.h"

class checkingAccount : public Account {
public:
	void statement();
	void deposit(float);
	void withdrawal(float);
	void payCheck(float);
	checkingAccount(int, string);
};

checkingAccount::checkingAccount(int num, string name) : Account(num, name) {
}

void checkingAccount::statement() {
	cout << this->getOwnerName() << endl;
	cout << this->getAccountNumber() << endl;
	cout << this->getBalance() << endl;
}

void checkingAccount::deposit(float cash) {
	this->credit(cash);
}

void checkingAccount::withdrawal(float cash) {
	this->debit(cash);
}

void checkingAccount::payCheck(float check) {
	this->debit(check);

	double bal = this->getBalance();
	if (bal < 0.00)
		this->debit(30.00);
}
