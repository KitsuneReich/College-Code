//---------------------------------------------------------
// LAB 1: A Simple Program
// CMPE 012 Summer 2018 University of California Santa Cruz
// 
// Boothroyd, Nichole
// nboothro
//
// Language: C
// 
// Description: This program iterates from 1800 to 2500, printing
// out "leap" if that year is a leap year.
//
// Usage:  gcc Leap.c -o leap
//	   ./leap 
//
// Notes: Thank you for your time, graders.
//---------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	bool debug = false;
	unsigned int lineCount = 1;
	
	//Iterating through the requested years and printing to screen
	for(unsigned int i = 1800; i <= 2500; i++) {
		
		//Checking for output requirements
		if(debug == true) {
			printf("%d: ", lineCount);
			lineCount++;
		}

		//If year is divisible by 4 AND 100 AND 400, print leap
		if(i%4 == 0 && i%100 == 0 && i%400 == 0) {
			printf("leap\n");
		}
		//Else if year is divisible by 4 AND NOT 100, print leap
		else if(i%4 == 0 && i%100 != 0) {
			printf("leap\n");
		}
		//Else, print the year
		else {
			printf("%d\n", i);
		}
	}
	
	//return value for main
	return 0;
}
