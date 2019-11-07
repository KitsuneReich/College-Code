//Nichole Boothroyd     cruzID: nboothro        Assignment: pa4
//  Graph.c
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

// structs --------------------------------------------------------------------
//private Graph type
typedef struct GraphObj{
    int order, size, source;
    List* adj;
    char* color;
    int* d;
    int* p;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------
//newGraph()
//Returns reference to a new empty Graph object
Graph newGraph(int n) {
    Graph G;
    G = malloc(sizeof(struct GraphObj));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    G->adj = malloc((n+1)*sizeof(List));
    G->color = malloc((n+1)*sizeof(char));
    G->d = malloc((n+1)*sizeof(int));
    G->p = malloc((n+1)*sizeof(int));
    
    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList();
        G->color[i] = 'w';
        G->d[i] = INF;
        G->p[i] = NIL;
    }
    return (G);
}

//freeGraph()
//Frees all heap memory associated wtih Graph *pG and sets *pG to NULL
void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
        Graph G = *pG;
        for (int i = 1; i <= getOrder(G); i++) {
            freeList(&G->adj[i]);
        }
        free(G->adj);
        free(G->color);
        free(G->d);
        free(G->p);
    }
    free(*pG);
    *pG = NULL;
}

// Access functions -----------------------------------------------------------
//getOrder()
//Returns the order of a graph
int getOrder(Graph G) {
    return (G->order);
}

//getSize()
//Returns the size of a graph
int getSize(Graph G) {
    return(G->size);
}

//getSource()
//Returns the source vertex most recently used by BFS()
int getSource(Graph G) {
    return (G->source);
}

//getParent()
//Returns the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS
//has not been called
int getParent(Graph G, int u) {
    if( u < 1 || u > getOrder(G) ){
        printf("Graph Error: u is outside the range of vertices for getParent()\n");
        exit(1);
    }
    return (G->p[u]);
}

//getDist()
//Reurns the distance from the most recent BFS source to vertex u or INF if BFS
//has not been called
//Pre: 1 <= u <= getOrder(g)
int getDist(Graph G, int u) {
    if( u < 1 || u > getOrder(G) ){
        printf("Graph Error: u is outside the range of vertices for getDist()\n");
        exit(1);
    }
    return (G->d[u]);
}


//getPath()
//Appends to the List L the vertices of a shortest path in the graph from source
//to u, or appends to L the value NIL if no such path exists
//Pre: getSource(G) != NIL
void getPath(List L, Graph G, int u) {
    if( getSource(G) == NIL ){
        printf("Graph Error: getPath() requires running BFS at least once\n");
        exit(1);
    }
    int i = u;
    if( !isEmpty(L)) {
        while (getParent(G, i) != NIL) {
            append(L, i);
            i = getParent(G, i);
        }
        append(L, i);
    }
    else if (isEmpty(L) && getParent(G, i) == NIL) {
        append(L, NIL);
    }
    else if (isEmpty(L)) {
        while (getParent(G, i) != NIL) {
            prepend(L, i);
            i = getParent(G, i);
        }
    prepend(L, i);
    }
}

//Manipulation Procedures---------------------------------------------------------
//makeNull()
//Restores graph to original no edge state
void makeNull(Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->adj[i]);
    }
}

//addEdge()
//Inserts an edge joining u to v, and an edge jointing v to u [bidirectional]
//Pre: 1 <= u <= getOrder(g)
//Pre: 1 <= v <= getOrder(g)
void addEdge(Graph G, int u, int v) {
    if( u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G) ){
        printf("Graph Error: u or v is outside the range of vertices\n");
        exit(1);
    }
    else if (isEmpty(G->adj[u])) {
        append(G->adj[u], v);
    }
    else {
        moveFront(G->adj[u]);
        for (int i = 1; i <= v; i++) {
            if (get(G->adj[u]) < v) {           //if v is bigger than the cursor's
                moveNext(G->adj[u]);            //element
                if (index(G->adj[u]) == -1) {   //if passed the end of the List
                    append(G->adj[u], v);
                    break;
                }
            }
            else if (get(G->adj[u]) > v) {      //if v is smaller than cursor
                insertBefore(G->adj[u], v);     //element
                break;
            }
        }
    }
    //switch now to insert into v's adj
    if (isEmpty(G->adj[v])) {
        append(G->adj[v], u);
    }
    else {
        moveFront(G->adj[v]);
        for (int i = 1; i <= u; i++) {
            if (get(G->adj[v]) < u) {
                moveNext(G->adj[v]);
                if (index(G->adj[v]) == -1) {
                    append(G->adj[v], u);
                    break;
                }
            }
            else if (get(G->adj[v]) > u) {
                insertBefore(G->adj[v], u);
                break;
            }
        }
    }
    G->size += 1;                               //Increment edge counter
}

//addArc()
//Inserts an edge joining u to v only
//Pre: 1 <= u <= getOrder(g)
//Pre: 1 <= v <= getOrder(g)
void addArc(Graph G, int u, int v) {
    if( u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G) ){
        printf("Graph Error: u or v is outside the range of vertices\n");
        exit(1);
    }
    else if (isEmpty(G->adj[u])) {
        append(G->adj[u], v);
    }
    else {
        moveFront(G->adj[u]);
        for (int i = 1; i <= v; i++) {
            if (get(G->adj[u]) < v) {           //if v is bigger than the cursor's
                moveNext(G->adj[u]);            //element
                if (index(G->adj[u]) == -1) {   //if passed the end of the List
                    append(G->adj[u], v);
                    break;
                }
            }
            else if (get(G->adj[u]) > v) {      //if v is smaller than cursor
                insertBefore(G->adj[u], v);     //element
                break;
            }
        }
    }
    G->size += 1;
}

//BFS()
//Performs BFS on a source vertex, producing a BFS tree
void BFS(Graph G, int s) {
    G->source = s;
    for (int i = 1; i < getOrder(G); i++) {
        G->color[i] = 'w';
        G->d[i] = INF;
        G->p[i] = NIL;
    }
    G->color[s] = 'g';
    G->d[s] = 0;
    G->p[s] = NIL;
    List Q = newList();
    append(Q, s);
    while (!(isEmpty(Q))) {
        moveFront(Q);
        int x = get(Q);
        deleteFront(Q);
        if (isEmpty(G->adj[x])) {           //if the current vertex has no edges
            G->color[x] = 'b';
            break;
        }
        moveFront(G->adj[x]);
        while (index(G->adj[x]) != -1) {
            int y = get(G->adj[x]);
            if (G->color[y] == 'w') {
                G->color[y] = 'g';
                G->d[y] = (G->d[x] + 1);
                G->p[y] = x;
                append(Q, y);
            }
            moveNext(G->adj[x]);
        }
        G->color[x] = 'b';
    }
    freeList(&Q);
}

// Other functions ---------------------------------------------------------------
//printGraph()
//Prints out the graph
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d:", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}




