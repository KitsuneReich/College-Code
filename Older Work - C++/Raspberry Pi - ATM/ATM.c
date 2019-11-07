#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "account.h"

using namespace std;
unsigned int sleep(unsigned int);
void die() {
	cout <<"BAD INPUT\n";
	exit (EXIT_FAILURE);
}

int main() 
{
int MENU = 0;					//Menu Default Screen
int button;
int PIN;					//var for PIN
double cash = 0.00;				//var for withdrawl amount

Account myChk;					//Dummy checking account
myChk.accountNumber = 00000017;
myChk.ownerName = "Sandi Cliff";
myChk.balance = 5.15;
myChk.key = 4242;

Account mySav;					//Dummy savings account
mySav.accountNumber = 00000016;
mySav.ownerName = "Rick Sanchez";
mySav.balance = 15.75;
mySav.key = 4242;

	while (cin)
	{

		if (MENU == 0) 		//Welcome Screen
		{
			cout << "\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |   * ~ Welcome to the Bank of Dank ~ *    | |\n"
			"\t| |                                          | |\n"
			"\t| |     Please enter your PIN number         | |\n"
			"\t| |           or 420 to quit:                | |\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n";

			cin >> PIN;			//Change for numpad

				if (PIN !=  mySav.key || PIN == myChk.key)
					MENU = 99;		//Invalid password

				if (PIN == mySav.key || PIN == myChk.key)
					MENU = 1;		//Correct password

				if (PIN == 420)
					break;			//Exit

				if (!cin)
					die();			//Error
		}

		else if (MENU == 1)	//Home Screen
		{
			cout << "\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |   * ~ Welcome to the Bank of Dank ~ *    | |\n"
			"\t| |     How can we help you today?           | |\n"
			"\t| |                                          | |\n"
			"\t| | 1]Balance Inquiry        2]Withdrawal    | |\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"      __| |420 to quit_______________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n";

			cin >> button;		//Change for button input
				if (button == 1)	//
					MENU = 2;
				if (button == 2)	//
					MENU = 3;
				if (button == 420)	//Change for numpad
					break;
		}

		else if (MENU == 2) 	//Blanace
		{
			cout << "\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n"
			"\t| |    Which account would you like to       | |\n"
			"\t| |                access?                   | |\n"
			"\t| |                                          | |\n"
			"\t| | 1]Savings                2]Checking      | |\n"
			"\t| |                                          | |\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
				"\t| |                                          | |\n";

			cin >> button;		//Change for button input

				if (button == 1) 	//Print savings balance
				{
					cout << "\n"
					"      __| |__________________________________________| |__\n"
					"     (__   __________________________________________   __)\n"
					"\t| |      Your current balance is:            | |\n"
					"\t| |                                          | |\n"
					"\t| |         " << mySav.getBalance() << "                            | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"      __| |__________________________________________| |__\n"
					"     (__   __________________________________________   __)\n"
					"\t| |                                          | |\n";
				sleep(10);
				MENU = 1;
				}


				if (button == 2)	//Print Checking Balance
				{	cout << "\n"
					"      __| |__________________________________________| |__\n"
					"     (__   __________________________________________   __)\n"
					"\t| |      Your current balance is:            | |\n"
					"\t| |                                          | |\n"
					"\t| |         " << myChk.getBalance() << "                             | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"      __| |__________________________________________| |__\n"
					"     (__   __________________________________________   __)\n"
					"\t| |                                          | |\n";

					sleep(10);
					MENU = 1;	//Back to Home Screen
				}
		}

		else if (MENU == 3) 	//Withdrawal
		{
			cout << "\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n"
			"\t| |    Which account would you like to       | |\n"
			"\t| |                access?                   | |\n"
			"\t| |                                          | |\n"
			"\t| | 1]Savings                2]Checking      | |\n"
			"\t| |                                          | |\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n";

			cin >> button;		//Change for button input


				if (button == 1) 	//Withdrawal from savings
				{
					cout << "\n"
					"      __| |__________________________________________| |__\n"
					"     (__   __________________________________________   __)\n"
					"\t| |                                          | |\n"
					"\t| |    How much would you like to withdraw?  | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"      __| |__________________________________________| |__\n"
					"     (__   __________________________________________   __)\n"
					"\t| |                                          | |\n";

					cin >> cash;
						if (mySav.debit(cash))
						{
							cout << "\n"
							"      __| |__________________________________________| |__\n"
							"     (__   __________________________________________   __)\n"
							"\t| |          Dispensing: Please take         | |\n"
							"\t| |               your treats.               | |\n"
							"\t| |                                          | |\n"
							"\t| |           Your new balance is:           | |\n"
							"\t| |         " << mySav.getBalance() << "                            | |\n"
							"\t| |                                          | |\n"
							"      __| |__________________________________________| |__\n"
							"     (__   __________________________________________   __)\n"
							"\t| |                                          | |\n";
					/*Place code here for motor control*/
							sleep(10);
							MENU = 1;	//Back to Home Screen
						}
				}
				if (button == 2) 	//Withdrawal from checking
				{
					cout << "\n"
					"      __| |__________________________________________| |__\n"
					"     (__   __________________________________________   __)\n"
					"\t| |                                          | |\n"
					"\t| |    How much would you like to withdraw?  | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"\t| |                                          | |\n"
					"      __| |__________________________________________| |__\n"
					"     (__   __________________________________________   __)\n"
					"\t| |                                          | |\n";

					cin >> cash;
						if (myChk.debit(cash))
						{
							cout << "\n"
							"      __| |__________________________________________| |__\n"
							"     (__   __________________________________________   __)\n"
							"\t| |          Dispensing: Please take         | |\n"
							"\t| |               your treats.               | |\n"
							"\t| |                                          | |\n"
							"\t| |           Your new balance is:           | |\n"
							"\t| |         " << myChk.getBalance() << "                            | |\n"
							"\t| |                                          | |\n"
							"      __| |__________________________________________| |__\n"
							"     (__   __________________________________________   __)\n"
							"\t| |                                          | |\n";
					/*Place code here for motor control*/
							sleep(10);
							MENU = 1;		//Back to Home Screen
						}
				}
		}
		else if (MENU == 99) {
			cout << "\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |           Invalid PIN number             | |\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"\t| |                                          | |\n"
			"      __| |__________________________________________| |__\n"
			"     (__   __________________________________________   __)\n"
			"\t| |                                          | |\n";
			sleep(5);
			MENU = 0;  //Request PIN again

		}
	}
	return 0;
}
