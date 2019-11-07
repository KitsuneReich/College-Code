#include <iostream>
#include <string>

using namespace std;

struct employee {
	string name;
	float payRate;
	float hours;
};

float HourlyRate(employee);

int main () {
	employee Samantha;
	Samantha.name = "Samantha";
	cout << "How many hours worked?\n";
	cin >> Samantha.hours;
	Samantha.payRate = 9.00;
	//Samantha.hours = 40.5;

	cout << "For " << Samantha.hours << " hours of work, pay " << Samantha.name << " $" << HourlyRate(Samantha)<< endl;

	system ("PAUSE");
	return 0;
}

float HourlyRate ( employee peon) {
	float pay = (peon.hours * peon.payRate);
	return pay;
}