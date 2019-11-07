//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  The definitions for the custom Rectangle class.
//
// Usage:        #include "rectangle.h"
//
//---------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "rectangle.h"

Rectangle::Rectangle () {
		l = 0;
		w = 0;
}
Rectangle::Rectangle (double length, double width) {
	l = length;
	w = width;
}
Rectangle::Rectangle (const Rectangle& src) {
		l = src.l;
		w = src.w;
}
void Rectangle::set_length(double new_length) {
	l = new_length;
}
void Rectangle::set_width (double new_width) {
	w = new_width;
}
double Rectangle::get_length() {
	return l;
}
double Rectangle::get_width() {
	return w;
}
double Rectangle::area() {
	return ( l * w );
}
string Rectangle::description() {
return "Length: " + to_string(l) + "\n" + "Width: " + to_string(w) + "\n";
}
