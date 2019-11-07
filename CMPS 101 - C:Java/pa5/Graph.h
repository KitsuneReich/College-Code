//Nichole Boothroyd     cruzID: nboothro        Assignment: pa5
//  Graph.h
//  
//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef Graph_h
#define Graph_h
#define UNDEF -17
#define NIL 0

#include <stdio.h>
#include "List.h"

// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

//newGraph()
//Creates a new graph with n vertices
Graph newGraph(int n);

//freeGraph()
//Frees all heap memory associated wtih Graph *pG and sets *pG to NULL
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------
//getOrder()
//Returns the order of a graph
int getOrder(Graph G);

//getSize()
//Returns the size of a graph
int getSize(Graph G);

//getSource()
//Returns the source vertex most recently used by BFS()
int getSource(Graph G);

//getParent()
//Returns the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS
//has not been called
int getParent(Graph G, int u);

//getDiscover()
//Returns the discover time of a vertex u in the DFS forest
//Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u);

//getFinish()
//Returns the finish time of a vertex u in the DFS forest
//Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u);


//Manipulation Procedures---------------------------------------------------------
//makeNull()
//Restores graph to original no edge state
void makeNull(Graph G);

//addEdge()
//Inserts an edge joining u to v, and an edge jointing v to u [bidirectional]
//Pre: 1 <= u <= getOrder(g)
//Pre: 1 <= v <= getOrder(g)
void addEdge(Graph G, int u, int v);

//addArc()
//Inserts an edge joining u to v only
//Pre: 1 <= u <= getOrder(g)
//Pre: 1 <= v <= getOrder(g)
void addArc(Graph G, int u, int v);

//DFS()
//Performs DFS on a source vertex, producing a DFS forest
void DFS(Graph G, List S);

// Other functions -----------------------------------------------------------
//transpose()
//Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

//copyGraph()
//Returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G);

//printGraph()
//Prints out the graph
void printGraph(FILE* out, Graph G);

#endif /* Graph_h */
