#include <iostream>
#include <string>

using namespace std;

string ETA(float, float);

int main () {
	float s;
	float d;

	cout << "How fast are you going?\n";
	cin >> s;
	cout << "How far until your destination?\n";
	cin >> d;
	cout << ETA(s, d) << endl;

	system ("PAUSE");
	return 0;
}

string ETA( float speed, float distance) {
	double time = (distance/speed);
	int time_hrs = (time * 60);
	int output_hrs = ((time * 60)/60);
	int output_min = (time_hrs % 60);
	
	string output = to_string(output_hrs) + " hours, " + to_string(output_min) + " minutes, ";
	return output;
}