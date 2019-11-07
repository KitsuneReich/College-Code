//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This is the main program to test the custom Account class and the
//               subclasses for savingAccount and checkingAccount.
//
// Usage:        g++ Account.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "account.h"
#include "checking.h"
#include "savings.h"

using namespace std;

int main() {
	checkingAccount myAcc(12345, "Sandi Cliff");
	savingsAccount mySav(424242, "Rick Sanchez", 0.2);
	

	myAcc.statement();
	myAcc.deposit(20.50);
	myAcc.statement();
	myAcc.withdrawal(5.25);
	myAcc.statement();
	myAcc.payCheck(17.25);
	myAcc.statement();

	mySav.statement();
	mySav.deposit(50.00);

	cout << "Withdrawing from savings 6 times:\n";
	mySav.withdrawal(1.25);
	mySav.withdrawal(1.25);
	mySav.withdrawal(1.25);
	mySav.withdrawal(1.25);
	mySav.withdrawal(1.25);
	mySav.withdrawal(1.25);
	mySav.statement();

	cout << "Withdrawing from savings:\n";
	mySav.withdrawal(1.25);
	mySav.statement();

	cout << "Paying interest on account:\n";
	mySav.payMonthlyInterest();
	mySav.statement();

	//system("PAUSE");
    return 0;
}
