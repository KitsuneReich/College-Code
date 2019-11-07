//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  The main program to run/test the Leaderboard class. Adds/sorts 
//               scores. High scores are saved to a .txt file and then loaded on
//               subsequent runs.
//
// Usage:        g++ main.cpp
//                ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <vector>

#include "score.h"
using namespace std;

int main() {

	Leaderboard<game> screen;

	screen.load();
    
    cout << "LOADED LEADERBOARD" << endl;
	screen.print();
    
    cout << "ADDING NEW SCORES" << endl;
    
	screen.addScore("FOX", 2100);
	screen.addScore("FOO", 3100);
	screen.addScore("BAR", 4100);
    
    screen.sort();
	
	screen.store();
    
    cout << "UPDATED LEADERBOARD" << endl;
	screen.print();

//	system("PAUSE");
	return 0;
}