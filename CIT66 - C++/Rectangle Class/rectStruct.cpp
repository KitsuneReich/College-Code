//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  A program which utilizes a struct for creating rectangles with a
//               simple main() function to test it.
//
// Usage:        g++ rectStruct.cpp
//               ./a.out
//
//---------------------------------------------------------------------------------
#include <iostream>

using namespace std;

struct rect {
		double length;
		double width;
};

double area(rect R) {
	double area;
	area = (R.length* R.width);
	return area;
}
double perimeter(rect R) {
	double peri;
	peri = (2 * R.length) + (2 * R.width);
	return peri;
}
rect resize(rect R, double new_size) {
	R.length = (R.length * new_size);
	R.width = (R.width * new_size);
	return R;
}
void description(rect R) {
	cout << "The length of the rectangle is: " << R.length << endl;
	cout << "The width of the rectangle is: " << R.width << endl;
}
int main() {
	 rect my_rect;
	 my_rect.length = 4;
	 my_rect.width = 2;

    cout << "The perimeter is " << perimeter(my_rect) << endl << endl;
	 description(my_rect);
    
     cout << "\n\nResizing the rectangle by 0.5\n";
	 my_rect = resize(my_rect, 0.5);
	 description(my_rect);

//	 system ("PAUSE");
    return 0;
 }
