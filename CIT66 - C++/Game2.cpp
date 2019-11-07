//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  Guessing Game revisited to implement functions instead of having
//               the entire game contained within a loop.
//
// Usage:        g++ Game2.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
void playGame();
bool wantToPlay();
bool check(int, int);

int main (void) {
	srand(time(NULL));
	do {
		playGame();
	}while (wantToPlay());
	
	return 0;
}

void playGame() {
int rNum = (rand() % 10) + 1;		//Loops between 0-9, add 1 for 1-10
		int yourNum;
		int credits = 3;
		bool gameover = false;

		for (int i = 0; i < credits; i++) {
			cout << "Enter a number between 1 and 10:\n";
			cin >> ws;		//clean up white space
			int c = cin.peek();	//Peek ahead
			
			if (c == EOF) break;
			else if (isdigit(c)){
				cin >> yourNum;
				gameover = check(yourNum, rNum);
					if (gameover == false)
						continue;
					if (gameover == true)
						break;
			}
			else
				cout << "ERROR\n";
				exit(EXIT_FAILURE);
		}
}
bool wantToPlay() {
	char play;
	cout << "Would you like to play again? Y/N:";
	cin >> play;
		if (play == 'y' || play == 'Y'){
			return true;}
		else 
			return false;
}

bool check(int yourNum, int rNum) {
	if (yourNum <= 0 || yourNum > 10) {
       	 	cout << "Invalid Entry.\n";
       	 	return true;
        }

        if (yourNum < rNum) {
        	cout << "Too low. . .\n";
		return false;
	}
        if (yourNum > rNum) {
                cout << "Too high. . .\n";
        	return false;
	}
        if (yourNum == rNum) {
                cout << "We have a winner!\n";
               	return true;
        }
}
