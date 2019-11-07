//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This is the main function which utilizes the custom Tally class
//               and tests their funcs.
//
// Usage:        g++ TallyMain.cpp Tally.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Tally.h"

using namespace std;

int main() {
	Tally x(12);
	Tally y("XXXII");
	Tally z(5);
	int fox;

	cout << x.description() << endl;
	cout << y.description() << endl;
    cout << z.description() << endl;

    cout << "Enter a new value for the x tally:\n";
	cin >> fox;
	x.setValue(fox);
    cout << "The new x value is: " << x.getValue() << endl;

	cout << (z + z);
	cout << (z - x);
	cout << (z + 2);
	cout << (10 + z);
	cout << ( z - 5);
	cout << (35 - z);

//	system ("PAUSE");
    return 0;
}
