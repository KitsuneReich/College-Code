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

	screen.print();

	screen.addScore("FOX", 2100);
	screen.addScore("FOO", 3100);
	screen.addScore("BAR", 4100);

	screen.sort();

	screen.store();

	screen.print();

	system("PAUSE");
	return 0;
}