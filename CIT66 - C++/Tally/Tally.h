#pragma once
#include <string>

using namespace std;

class Tally {
private:
	int value;
public:
	Tally();
	Tally(int);
	Tally(string);
	string description();
	int getValue();
	void setValue(int);
	Tally operator+(const Tally&);
	Tally operator+(int);
	friend Tally operator+(int, const Tally&);
	Tally operator-(const Tally&);
	Tally operator-(int);
	friend Tally operator-(int, const Tally&);
	friend ostream& operator<<(ostream&, const Tally&);
};