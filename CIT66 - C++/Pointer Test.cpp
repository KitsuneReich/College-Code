//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This is test snippet for pointers.
//
// Usage:        g++ Pointer Test.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>

using namespace std;

int main() {
	int fox = 42;
	int *box = &fox;
	cout << &fox << endl;
	cout << *box << endl;

	//system("PAUSE");
	return 0;

}
