//
//  main.cpp
//  
//
//  Created by Nichole Boothroyd on 9/22/16.
//
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstddef>
#include <vector>
#include "table.h"

void uppercaseify(string& my_str);
void checkStr(string my_str);

using namespace std;

int main() {
    string input;
    vector<Table> treasure;
    
    while (cin) {
        cout << "Enter a command:" << endl;
        getline(cin,input);
        uppercaseify(input);
        checkStr(input);
    
    if (input.find("CREATE TABLE ")) {
        input.erase(1,13);
        Table temp;
        temp.rename(input);
        treasure.push_back(temp);
    }
        if (input.find("INSERT INTO ") {
            input.erase(1, 12);
            int length = find_first(" ");
        }

    }
    
return 0;    
}

void uppercaseify(string& my_str) {
    for (auto& c: my_str)
        c = toupper(c);
}

void checkStr(string my_str) {
    size_t found = my_str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234569890");
    if (found == string::npos)
        return;
    else {
        cout <<"BAD INPUT" << endl;
        exit (EXIT_FAILURE);
    }
    
}
