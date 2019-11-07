//Nichole Boothroyd     cruzID: nboothro        Assignment: pa4
//
//-----------------------------------------------------------------------------
// GraphTest.c
// Test client for testing Graph ADT
//-----------------------------------------------------------------------------
//
#include <stdio.h>
#include "Graph.h"

int main (){
    Graph A = newGraph(100);
    List C = newList();
    List L = newList();
    
    addEdge(A, 64, 4);
    addEdge(A, 64, 3);
    addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addEdge(A, 3, 42);
    BFS(A, 3);
    getPath(L, A, 64);
    append(C, 3);
    append(C, 64);
    
    printList(stdout, L);
    printf("\n");
    printList(stdout, C);
    printf("\n");
    
    moveFront(L);
    
    BFS(A, 2);
    getPath(L, A, 2);
    append(C, 2);
    
    printList(stdout, L);
    printf("\n");
    printList(stdout, C);
    printf("\n");
    
    getPath(L, A, 99);

    printList(stdout, L);
    printf("\n");
    printList(stdout, C);
    printf("\n");
    
    clear(L);
    clear(C);
    append(C, NIL);
    BFS(A, 99);
    getPath(L, A, 2);
    
    printList(stdout, L);
    printf("\n");
    printList(stdout, C);
    printf("\n");
    
    freeGraph(&A);
    freeList(&C);
    freeList(&L);
}

