//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This is the header file containing the class declarations for the
//               custom Rectangle class.
//
// Usage:        #include "rectangle.h"
//
//---------------------------------------------------------------------------------
#pragma once
#include <string>

using namespace std;

class Rectangle {
private:
	double l;
	double w;
public:
	void set_length(double);
	void set_width (double);
	double get_length();
	double get_width();
	double area();
	string description();
	Rectangle ();
	Rectangle (double, double);
	Rectangle (const Rectangle&);
};
