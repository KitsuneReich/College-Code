//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This is the subclass for savingsAccount. Note: payMonthlyInterest()
//               adds 1/12th (interest rate * balance) and there is a charge for
//               every withdrawal after the 6th.
//
// Usage:        #include "savings.h"
//
//---------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <string>
#include "account.h"

class savingsAccount : public Account {
private:
	int numOfWithdrawals;
	float interestRate;
public:
	void statement();
	void deposit(float);
	void withdrawal(float);
	void payMonthlyInterest();
	int getWithdrawal();
	savingsAccount(int, string, float);
};
savingsAccount::savingsAccount(int num, string name, float rate) : Account(num, name) {
	interestRate = rate;
	numOfWithdrawals = 0;
}

void savingsAccount::statement() {
	cout << this->getOwnerName() << endl;
	cout << this->getAccountNumber() << endl;
	cout << this->getBalance() << endl;
	cout << this->getWithdrawal() << endl;
}

void savingsAccount::deposit(float cash) {
	this->credit(cash);
}

void savingsAccount::withdrawal(float cash) {
	this->debit(cash);

	numOfWithdrawals++;
	if (numOfWithdrawals > 6)
		this->debit(15.00);
}

void savingsAccount::payMonthlyInterest() {
	float total;
	total = ((1/12) * (interestRate * this->getBalance()));
	
	this->credit(total);
}

int savingsAccount::getWithdrawal() {
	return numOfWithdrawals;
}
