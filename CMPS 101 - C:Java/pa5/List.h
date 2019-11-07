// Nichole Boothroyd    cruzID: nboothro  Assignment: pa5
//  List.h

#ifndef List_h
#define List_h


//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L);

// length()
// Returns the length of L.
int length(List L);

//index()
//If the cursor is defined, returns the index of the cursor element
//Otherwise, return -1
int index(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L);

//back()
//Returns the value at the back of L.
//Pre: !isEmpty(L)
int back(List L);

//get()
//Returns cursor element
//Pre: !this.isEmpty()
//Pre: index needs to be defined
int get(List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

//clear ()
//Resets this List to its original empty state
//Pre: !this.isEmpty()
void clear(List L);

//moveFront()
//Places the cursor under front element, or does nothing [not even an error message?]
//Pre: !this.isEmpty()
void moveFront(List L);

//moveBack()
//Places the cursor under back element, or does nothing
//Pre: !this.isEmpty()
void moveBack(List L);

//movePrev ()
//If cursor is defined and not at front, moves cursor one step toward
//front of this List, if cursor is defined and at front, cursor becomes
//undefined, if cursor is undefined does nothing.
void movePrev(List L);

//moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L);

// append()
// Places new data element at the end of L
void append(List L, int data);

// prepend()
// Insert new element into this List.
// If List is non-empty, insertion takes place before front element
void prepend(List L, int data);

//insertBefore()
//Insert new element before cursor
//Pre: length()>0, index()>=0
void insertBefore(List L, int data);

//insertAfter()
//Insert new element after cursor
//Pre: length()>0, index()>=0
void insertAfter(List L, int data);

// deleteFront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L);

//deleteBack()
//Deletes the back element
//Pre: !this.isEmpty()
void deleteBack(List L);

//delete()
//Deletes cursor element, making it undefined
//Pre: length()>0, index()>=0;
void delete(List L);

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L);

//copyList()
//Returns a new List identical to this List
List copyList(List L);

#endif
