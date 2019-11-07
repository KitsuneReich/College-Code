//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language: C++
//
// Description: This is the main function which utilizes the custom Stack and Tally
//              classes to create a stack of Tally objects and tests their funcs.
//
// Usage:       g++ Main.cpp
//              ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <cctype>
#include "stack.h"
#include "tally.h"
using namespace std;

int main() {
	Stack<Tally> my_stack;
	Tally x(12), y(15), z(21);

	my_stack.push(x);
    cout<< "Pushing: " << x.getValue() << "\n";
	my_stack.push(y);
    cout<< "Pushing: " << y.getValue() << "\n";
    my_stack.push(z);
    cout<< "Pushing: " << z.getValue() << "\n";
    
	cout << "Popping:\n";
    cout << my_stack.pop().description() << "\n";
	
	cout << "Popping Again:\n";
	cout << my_stack.pop().description() << "\n";
    
	//system("PAUSE");
	return 0;
	}
