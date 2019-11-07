#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.cc"
using namespace std;

void uppercaseify(string& my_str);

int main () {

    BST my_tree;
    string operation;
    int data;

    while (cin) {
        cin >> operation;
        uppercaseify(operation);

        if (!cin || cin.eof() || operation == "EXIT" ) {
            exit(EXIT_SUCCESS);
        }
        if (operation == "PRINT") {
            my_tree.print();
        }
        if (operation == "INSERT") {
            cin >> data;
            my_tree.addLeaf(data);
        }
        if (operation == "DELETE") {
            cin >> data;
            my_tree.deleteNode(data);
        }
        if (operation == "FIND") {
            cin >> data;
            my_tree.search(data);
        }



    }





    return 0;
}

void uppercaseify(string& my_str) {
    for (auto& c: my_str)
        c = toupper(c);
}

