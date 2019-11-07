//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language: C++
//
// Description: This is the custom generic FILO stack class.
//
// Usage:       #include "stack.h"
//
//---------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <array>
#include <cstdlib>
using namespace std;


template <class T>
class Stack {
private:
	int index;
	array<T, 10> data;
public:
	Stack() { index = 0; }
	void push(T);
	T pop();
	void print();
};

template <typename T> void Stack<T>::push(T new_data) {
	this->data[index] = new_data;
	index++;
}

template <typename T> T Stack<T>::pop() {
	//if (data.size() <= 0) { die(); }
    index--;
    T obj = this->data[index];
    return obj;

}
template <typename T> void Stack<T>::print() {	
	cout << this->data[index].getValue() << endl;
}
