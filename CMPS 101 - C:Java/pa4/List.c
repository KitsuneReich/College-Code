//  Nichole Boothroyd    cruzID: nboothro  Assignment: pa2
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    int length;
    int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL) {
        while( !isEmpty(*pL) ) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}


// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
    if( L==NULL ){
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(1);
    }
    return(L->length==0);
}

// length()
// Returns the length of L.
int length(List L){
    if( L==NULL ){
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return(L->length);
}

//index()
//If the cursor is defined, returns the index of the cursor element
//Otherwise, return -1
int index(List L){
    if( L==NULL ){
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }
    return(L->index);  //cursor defaulted at -1
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
    if( L==NULL ){
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
    return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L){
    if( L==NULL ){
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling back() on an empty List\n");
        exit(1);
    }
    return(L->back->data);
}

//get()
//Returns cursor element
//Pre: !this.isEmpty()
//Pre: index needs to be defined
int get(List L) {
    if( L==NULL ){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling get() on an empty List\n");
        exit(1);
    }
    if( index(L) < 0) {
        printf("List Error: calling get() on an undefined cursor\n");
        exit(1);
    }
    else {
        Node temp = L->front;
        for (int i = 1; i<= index(L); i++) {
            temp = temp->next;
        }
        return(temp->data);
    }
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
    int eq = 0;
    Node N = NULL;
    Node M = NULL;
    
    if( A==NULL || B==NULL ){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }
    
    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;
    while( eq && N!=NULL){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------

//clear ()
//Resets this List to its original empty state
//Pre: !this.isEmpty()
void clear(List L) {
    if( L==NULL ){
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
/*    if( isEmpty(L) ){
        printf("List Error: calling clear() on an empty List\n");
        exit(1);
    }
 */
    else {
        while (length(L) > 0) {
            deleteBack(L);
        }
    }
}
    
//moveFront()
//Places the cursor under front element, or does nothing
//Pre: !this.isEmpty()
void moveFront(List L) {
    if( L==NULL ){
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling moveFront() on an empty List\n");
        exit(1);
    }
    else {
        L->index = 0;
    }
}

//moveBack()
//Places the cursor under back element, or does nothing
//Pre: !this.isEmpty()
void moveBack(List L) {
    if( L==NULL ){
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling moveBack() on an empty List\n");
        exit(1);
    }
    else {
        L->index = (length(L) - 1);
    }
}

//movePrev ()
//If cursor is defined and not at front, moves cursor one step toward
//front of this List, if cursor is defined and at front, cursor becomes
//undefined, if cursor is undefined does nothing.
void movePrev(List L) {
    if( L==NULL ){
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling movePrev() on an empty List\n");
        exit(1);
    }
    if( index(L) == -1){
        //do nothing
    }
    else {
        L->index--;
    }
}

//moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L) {
    if( L==NULL ){
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling moveNext() on an empty List\n");
        exit(1);
    }
    if( index(L) == -1) {
        //do nothing
    }
    else {
        L->index++;
        if( index(L)>= length(L)) {  //If the index >= length:
            L->index = -1;              //Cursor beomes undefined
        }
    }
}

// append()
// Places new data element at the end of L
void append(List L, int data)
{
    Node N = newNode(data);
    
    if( L==NULL ){
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ) {
        L->front = L->back = N;
    }else{
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}

// prepend()
// Insert new element into this List.
// If List is non-empty, insertion takes place before front element
void prepend(List L, int data) {
    Node N = newNode(data);
    
    if( L==NULL ){
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ) {
        L->front = L->back = N;
    }
    else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    }
    L->length++;
    L->index++;
}

//insertBefore()
//Insert new element before cursor
//Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
    if( L==NULL ) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ) {
        printf("List Error: calling insertBefore() on an empty List\n");
        exit(1);
    }
    if( index(L) < 0) {
        printf("List Error: calling insertBefore() on an undefined cursor\n");
        exit(1);
    }
    else if( index(L) == 0) {                //If inserting before first element
        prepend(L, data);
    }
    else {
        Node N = newNode(data);
        Node temp = L->front;
        for(int i = 1; i <= index(L); i++) {
            temp = temp->next;
        }
        N->next = temp;
        N->prev = temp->prev;
        temp->prev->next = N;
        temp->prev = N;
        L->length++;
        L->index++;                     //maintain cursor position
    }
}

//insertAfter()
//Insert new element after cursor
//Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
    if( L==NULL ) {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ) {
        printf("List Error: calling insertAfter() on an empty List\n");
        exit(1);
    }
    if( index(L) < 0) {
        printf("List Error: calling insertAfter() on an undefined cursor\n");
        exit(1);
    }
    if( index(L) == (length(L) - 1)) {  //If inserting after last element
        append(L, data);
    }
    else {
        Node N = newNode(data);
        Node temp = L->front;
        for(int i = 1; i <= index(L); i++) {
            temp = temp->next;
        }
        temp->next->prev = N;
        N->next = temp->next;
        N->prev = temp;
        temp->next = N;
        L->length++;
    }
}

// deleteFront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L){
    Node N = NULL;
    
    if( L==NULL ){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(1);
    }
    N = L->front;
    if( length(L)>1 ) {
        L->front = L->front->next;
        L->front->prev = NULL;
        if( index(L) == 0) {
            L->index = -1;
        }
        else {
            L->index--;
        }
    }else{
        L->front = L->back = NULL;
        L->index = -1;
    }
    L->length--;
    freeNode(&N);
}

//deleteBack()
//Deletes the back element
//Pre: !this.isEmpty()
void deleteBack(List L){
    Node N = NULL;
    
    if( L==NULL ){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling deleteBack() on an empty List\n");
        exit(1);
    }
    N = L->back;
    if( length(L) > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
        if(index(L) == (length(L) - 1)) {
            L->index = -1;
        }
    }
    else {
        L->front = L->back = NULL;
        L->index = -1;
    }
    L->length--;
    freeNode(&N);
}

//delete()
//Deletes cursor element, making it undefined
//Pre: length()>0, index()>=0;
void delete(List L) {
    if( L==NULL ) {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ) {
        printf("List Error: calling delete() on an empty List\n");
        exit(1);
    }
    if( index(L) < 0) {
        printf("List Error: calling delete() on an undefined cursor\n");
        exit(1);
    }
    else if( index(L) == 0) {        //If the cursor is pointing at the front
        deleteFront(L);
        L->index = -1;
    }
    else if( index(L) == (length(L) - 1)) {  //If cursor is pointing at back
        deleteBack(L);
        L->index = -1;
    }
    else {
        Node temp = L->front;
        for(int i = 1; i <= index(L); i++) {
            temp = temp->next;
        }
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        freeNode(&temp);
        L->length--;
        L->index = -1;
    }
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
    Node N = NULL;
    
    if( L==NULL ){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }
    
    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, " %d", N->data);
    }
    //printf("\n");
}

//copyList()
//Returns a new List identical to this List
List copyList(List L) {
    List Q = newList();
    Node N = L->front;
    
    while(N != NULL) {
        append(Q, N->data);
        N = N->next;
    }
    return Q;
}
