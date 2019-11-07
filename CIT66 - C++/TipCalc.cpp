//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This program asks a user for the cost of a meal and calculates a
//               range of tip options.
//
// Usage:        g++ TipCalc.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	double check = 0.00;
	double lowTip = 0.10;
	double midTip = 0.15;
	double highTip = 0.20;

	cout << "How much did your meal cost?\n$";
	cin >> check;
	cout << setprecision (3)
		<< "For mediocre service:\t$" << (check * lowTip)<<endl
		<< "For good service:\t$" << (check * midTip)<<endl
		<< "For great service:\t$" << (check * highTip)<<endl;

	system ("PAUSE");

	return 0;
}
