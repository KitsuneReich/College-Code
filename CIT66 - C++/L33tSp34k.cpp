//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This program asks a user for their name and then returns a
//               reformatted version of that string in "Leet Speak."
//
// Usage:        g++ L33tSp34k.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
#include <string>

using namespace std;

int main() {
char array[20];
string name;

cout << "Enter your name:\n";
getline(cin, name);
int size = name.size();
cout<< "Your name in L33t Sp34k is:\n";

for (int i = 0; i<size; i++){
	if (name[i] == 'a' || name[i] == 'A') {cout << 4; continue;}
	if (name[i] == 'e' || name[i] == 'E') {cout << 3; continue;}
	if (name[i] == 'i' || name[i] == 'I') {cout << "|"; continue;}
	if (name[i] == 'o' || name[i] == 'O') {cout << 0; continue;}
	if (name[i] == 'b' || name[i] == 'B') {cout << 8; continue;}
	if (name[i] == 's' || name[i] == 'S') {cout << 5; continue;}
	
	else
		cout << name[i];
}
cout<<endl;

//system ("PAUSE");

return 0;

}
