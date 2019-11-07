//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This is the main function which utilizes the custom Rectangle class
//               and tests its funcs.
//
// Usage:        g++ RectangleMain.cpp rectangle.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
#include "rectangle.h"

using namespace std;

int main() {
	Rectangle fox;
	Rectangle box (2.54, 5.1);
	Rectangle sox (box);

	double temp1, temp2;

	cout << "Enter the length and width of the first rectangle:\n";
	cin >> temp1 >> temp2;
	fox.set_length(temp1);
	fox.set_width(temp2);

	cout << fox.description() << endl;
	cout << sox.description() << endl;
	
cout << "The first rectangle has an area of " << fox.area() << endl;
	cout << "The second rectangle has an area of " << box.area() << endl;
	cout << "The third rectangle has an area of " << sox.area() << endl;

//	system ("PAUSE");
    
    return 0;
}
