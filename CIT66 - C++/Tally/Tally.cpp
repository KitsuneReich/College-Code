#include <iostream>
#include <string>
#include "Tally.h"


	Tally::Tally() {
		value = 0;
	}
	Tally::Tally(int new_value) {
		value = new_value;
	}
	Tally::Tally(string new_value) {
		this->value = 0;
		for (int i = 0; i<= new_value.length(); i++) {
		if (new_value[i] == 'X')
			this->value+= 5;
		if (new_value[i] == 'I')
			this->value+= 1;
		}
	}
	string Tally::description() {
		return to_string(value);
	}
	int Tally::getValue() {
		return value;
	}
	void Tally::setValue(int new_value) {
		value = new_value;
	}
	Tally Tally::operator+(const Tally& tal) {
		value = value + tal.value;
		return value;
	}
	Tally Tally::operator+(int add_value) {
		value += add_value;
		return value;
	}
	Tally operator+(int op1, const Tally& op2) {
		Tally newTally;
		newTally.value = op1 + op2.value;
		return newTally;
	}
	Tally Tally::operator-(const Tally& tal) {
		value = value - tal.value;
		return value;
	}
	Tally Tally::operator-(int sub_value) {
		value -= sub_value;
		return value;
	}
	Tally operator-(int op1, const Tally& op2) {
		Tally newTally;
		newTally.value = op1 - op2.value;
		return newTally;
	}
	ostream& operator<<(ostream& os, const Tally& tal) {
		os << "The current tally is " << tal.value << endl;
		return os;
	}