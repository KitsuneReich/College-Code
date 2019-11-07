#pragma once
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

struct Account {
	int accountNumber;
	int key;
	string ownerName;
	double balance;


	string getOwnerName();
	int getAccountNumber();
	void setOwnerName(string);
	void setAccountNumber(int);
	double getBalance();
	void credit(double);
	bool debit(double);
};

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

bool Account::debit(double charge) {
	if (charge > balance) {
		cout << "\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n"
			"\t| |             Insufficient Funds           | |\n"
			"\t| |                                          | |\n"
			"\t| |                    ='[                   | |\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n";
		sleep(10);
		return false;
	}
	if (charge < 0) 
	{
		cout << "\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"\t| |                   U mad?                 | |\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n";
		sleep(10);
		return false;
	}

	else {
		balance -= charge;
		return true;
	}
}
