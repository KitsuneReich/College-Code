//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This program takes an age from user input and prints a response to
//               the console which is a gross generalization for that age.
//
// Usage:        g++ GrossGeneralizations.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
using namespace std;

int main () {
	int age;

	cout << "What is your age?\n";
	cin >> age;
	
	if (age < 0) {
		cout << "Does your mother know you're here?\n";}
	if (age > 0 && age < 5) {
		cout << "Did your parents read to you today?\n";}
	if (4 < age && age < 10) {
		cout << "Isn't it time for your little league game?\n";}
	if (9 < age && age < 16) {
		cout << "Don't worry. These are normal changes for your body.\n";}
	if (14 < age && age < 17) {
		cout << "SWEET SIXTEEN!\n";}
	if (16 < age && age < 18) {
		cout << "Have you gotten that acceptance letter to Stanford yet?\n";}
	if (17 < age && age < 21) {
		cout << "Don't stay up too late studying for that final exam.\n";}
	if (20 < age && age < 22) {
		cout << "SHOTS SHOTS SHOTS!!!\n"; }
	if (21 < age && age < 30) {
		cout << "I'm sure you'll get that second interview.\n";}
	if (29 < age && age < 35) {
		cout << "That corner office can be yours! A little networking goes "
			 << "a long way.\n";}
	if (34 < age && age < 45) {
		cout << "You deserved that new car.\n";}
    if (44 < age && age < 50) {
        cout << "Old age is catching up with you.\n";}
    if (49 < age && age < 55) {
		cout << "Congrats on making it over the hill!\n";}
	if (54 < age && age < 65) {
		cout << "All those doctor check ups really are in your best interest.\n";}
	if (64 < age && age < 75) {
		cout << "Now that you've retired, are you getting all that fishing in?\n";}
	if (74 < age && age < 100) {
		cout << "You must have so much wisdom to share.\n";}
	if (99 < age && age < 1,000) {
		cout << "You're a tough old bird.\n";}
	if (999 < age) {
		cout << "Welcome back, Dorian. . .\n";}

//	system ("PAUSE");

	return 0;
}
