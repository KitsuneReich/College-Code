//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  This is a Guessing Game utilizing RNG. Player has three chances to
//               guess correctly before being prompted if they wish to play again.
//
// Usage:        g++ GuessingGame.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main (void) {
	char play = 'y';
	int credits = 3;
	
	while (play == 'y' || play == 'Y') {
		srand(time(NULL));

		int rNum = (rand() % 10) + 1;		//Loops between 0-9, add 1 for 1-10
		int yourNum = 0;

		for (int i = 0; i < credits; i++) {
			cout << "\n\nEnter a number between 1 and 10:\n";
            if(i == 2) {
                cout << "Last chance to guess!\n";
            }
			cin >> yourNum;

			if (yourNum < 0 || yourNum > 10) {
				cout << "If you're not going to play by the rules, "
					 << "then you cant't play at all.\n\n";
				play = 'n';
				break;
			}

			if (yourNum < rNum) {
				cout << "Too low. . .\n";
				continue;
			}
			if (yourNum > rNum) {
				cout << "Too high. . .\n";
				continue;
			}
			if (yourNum == rNum) {
				cout << "We have a winner!\nWould you like to play again? Y/N:";
				cin >> play;
				break;
			}
		}
        cout << "Better Luck Next Time!\nWould you like to play again? Y/N:\n";
        cin >> play;
	}
		return 0;
}
