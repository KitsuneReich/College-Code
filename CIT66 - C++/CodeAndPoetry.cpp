//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  An exercise in cout statements and escape characters. This program
//               prints out a formatted poem, "O Sweet Spontaneous" by
//               E.E. Cummings, before waiting for user input to quit.
//
// Usage:        g++ CodeAndPoetry.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>
using namespace std;

int main(void)
{
	cout << "O sweet spontaneous\n" <<
		"earth how often have\n" <<
		"the\n" <<
		"doting\n" <<
		"\t\tfingers of\n" <<
		"prurient philosophers pinched\n" <<
		"and\n" <<
		"poked\n\n" <<
		"thee\n" <<
		",has the naughty thumb\n" <<
		"of science prodded\n" <<
		"thy\n\n"
		"\tbeauty\t    .how\n" <<
		"often have religions taken\n" <<
		"thee upon their scraggy knees\n" <<
		"squeezing and\n\n" <<
		"buffeting thee that thou mightest conceive\n" <<
		"gods\n" <<
		"\t(but\n" <<
		"true\n\n" <<
		"to the incomparable\n" <<
		"couch of death thy\n" <<
		"rhythmic\n" <<
		"lover\n\n" <<
		"\t\tthou answerest\n" <<
		"them only with\n" <<
		"\t\t\tspring)" << endl;

	cin.get();
	return 0;
}
