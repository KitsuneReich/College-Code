//Nichole Boothroyd     cruzID: nboothro        Assignment: pa4
//  Graph.h
//  
//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef Graph_h
#define Graph_h
#define INF -17
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

//getDist()
//Reurns the distance from the most recent BFS source to vertex x or INF if BFS
//has not been called
int getDist(Graph G, int u);

//getPath()
//Appends to the List L the vertices of a shortest path in the graph from source
//to u, or appends to L the value NIL if no such path exists
//Pre: getSource(G) != NIL
void getPath(List L, Graph G, int u);

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

//BFS()
//Performs BFS on a source vertex, producing a BFS tree
void BFS(Graph G, int s);

// Other functions -----------------------------------------------------------
//printGraph()
//Prints out the graph
void printGraph(FILE* out, Graph G);

#endif /* Graph_h */
