#include <iostream>
#include "tree.h"

using namespace std;

BST::BST(){
    root = NULL;

}

BST::Node* BST::createLeaf(int data) {
    Node* n = new Node;
    n->data = data;
    n->left = NULL;
    n->right = NULL;

    cout << "SUCCESS\n";


    return n;
}

void BST::addLeaf(int data) {
    addLeafPrivate(data, root);
}

void BST::addLeafPrivate(int data, Node* ptr) {
    if ( root == NULL) {
        root = createLeaf(data);
    }
    else if (data < ptr->data){
        if (ptr->left != NULL){
            addLeafPrivate(data, ptr->left);
        }
        else {
        ptr->left = createLeaf(data);
        }
    }
    else if (data > ptr->data){
        if (ptr->right != NULL){
            addLeafPrivate(data, ptr->right);
        }
        else {
        ptr->right = createLeaf(data);
        }
    }
    else if (data == ptr->data){
    cout << "DUPLICATE\n";
    return;
    }
    else {
        cout << "ERROR\n";
        return;
    }

}

void BST::print () {
    if (root  != NULL){
        cout << "BEGIN\n";
        printPrivate(root);
        cout << "END\n";
    }
    else
        printPrivate(root);
}

void BST::printPrivate(Node* ptr) {
    if (root == NULL){
    cout << "NULL\n";
    return;
    }
    if (root != NULL) {
        if (ptr->left != NULL){
            printPrivate(ptr->left);
            }
            cout << ptr->data << endl;
            if (ptr->right != NULL){
                printPrivate(ptr->right);
            }
    }
}

BST::Node* BST:: returnNode (int data) {
    return returnNodePrivate(data, root);

}

BST::Node* BST::returnNodePrivate(int key, Node* ptr) {
    if (ptr != NULL){
        if (ptr->data == key) {
        return ptr;
        }
        else {
            if (key < ptr->data){
                return returnNodePrivate(key, ptr->left);
            }
            else {
                return returnNodePrivate(key, ptr->right);
            }
        }
    }
    else {
    return NULL;
    }
}

void  BST::search(int data) {
    if (returnNodePrivate(data, root) != NULL)
        cout << "SUCCESS\n";
    else if (returnNodePrivate(data, root) == NULL)
        cout <<"NOT FOUND\n";
    else {
        cout <<"ERROR\n";
    }

}

int BST::findSmallestPrivate(Node* ptr){
    if (root == NULL){
        cout << "ERROR\n";
        return -777;
    }
    else if (ptr->left != NULL) {
            return findSmallestPrivate(ptr->left);
        }
    else {
            return ptr->data;
        }
}
int BST::findSmallest() {
    return findSmallestPrivate(root);
}

void BST::deletePrivate (int data, Node* parent) {
    if (root != NULL){
        if (root->data == data) {
            deleteRoot();
        }
        else {
            if (data < parent->data && parent->left != NULL) {
                parent->left->data == data ?
                deleteMatch(parent, parent->left, true):
                deletePrivate(data, parent->left);
            }
            else if (data > parent->data && parent->right != NULL) {
                parent->right->data == data ?
                deleteMatch(parent, parent->right, false) :
                deletePrivate(data, parent->right);
            }
            else {
                cout << "NOT FOUND\n";
            }
        }
    }
    else {
    cout << "EMPTY\n";
    }
}

void BST:: deleteNode(int data) {
    deletePrivate(data, root);
}

void BST::deleteRoot() {
    if (root != NULL) {
        Node* delptr = root;
        int root_data = root->data;
        int smallestRight;

        //Root has 0 children
        if (root->left == NULL && root->right == NULL){
            root = NULL;
            delete delptr;
        }

        //Root has 1 child
        else if (root->left == NULL && root->right != NULL) {
            root = root->right;
            delptr->right = NULL;
            delete delptr;
        }
        else if (root->right == NULL && root->left != NULL) {
            root = root->left;
            delptr->left = NULL;
            delete delptr;
        }
        //Root has 2 children
        else /*if(root->right != NULL && root->left !=NULL)*/{
            smallestRight = findSmallestPrivate(root->right);
            deletePrivate(smallestRight, root);
            root->data = smallestRight;

        }
    }

    else {
    cout << "ERROR\n";
    }
}

void BST::deleteMatch(Node* parent, Node* match, bool left) {
    if (root != NULL){
        Node* delptr;
        int match_data = match->data;
        int smallestRight;

        //0 children
        if (match->left == NULL && match->right == NULL) {
            delptr = match;
            //Is match left or right child of parent node?
            if (left == true) {
                parent->left = NULL;
            }
            else {
                parent->right = NULL;
            }
            //left = true ? parent->left = NULL : parent->right = NULL;
            delete delptr;
            cout <<"SUCCESS\n";
        }
        //1 child
        else if (match->left == NULL && match->right != NULL) {
            left == true ? parent->left = match->right : parent->right = match->right;
            match->right = NULL;
            delptr = match;
            delete delptr;
            cout <<"SUCCESS\n";
        }

        else if (match->left != NULL && match->right == NULL) {
            left == true ? parent->left = match->left : parent->right = match->left;
            match->left = NULL;
            delptr = match;
            delete delptr;
            cout <<"SUCCESS\n";
        }
        //2 children
        else {
            smallestRight = findSmallestPrivate(match->right);
            deletePrivate(smallestRight, root);
            match->data = smallestRight;
            cout <<"SUCCESS\n";

        }
    }
    else {
        cout << "ERROR\n";
    }
}







/*
 *  * Display Tree Structure
 *   */

/*void BST::display(node *ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->right, level+1);
        if (ptr == root)
            cout<<"Root->:  "<<ptr->info<<"|"<<height(ptr);
        else
        {
            for (i = 0;i < level;i++)
                cout<<"       ";
            cout<<((ptr->parent->left == ptr) ? "\\":"/") <<ptr->info<<"|"<<height(ptr);
        }
        cout<<endl;
        display(ptr->left, level+1);
    }
}


*/
