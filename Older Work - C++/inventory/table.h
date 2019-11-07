//
//  table.h
//  
//
//  Created by Nichole Boothroyd on 9/22/16.
//
//
#pragma once
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Table {
    vector<string> ID;
    string name;
    
public:
    void add(string);
    void rename(string);
};

void Table::add(string element) {
    ID.push_back(element);
}
void Table::rename(string new_name) {
    name = new_name;
}
