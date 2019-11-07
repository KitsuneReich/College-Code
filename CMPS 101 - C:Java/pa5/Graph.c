//Nichole Boothroyd     cruzID: nboothro        Assignment: pa5
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
    int* d;         //discover time
    int* f;         //finish time
    int* p;         //parent
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
    G->f = malloc((n+1)*sizeof(int));
    G->p = malloc((n+1)*sizeof(int));
    
    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList();
        G->color[i] = 'w';
        G->d[i] = UNDEF;
        G->f[i] = UNDEF;
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
        free(G->f);
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
//Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if( u < 1 || u > getOrder(G) ){
        printf("Graph Error: u is outside the range of vertices for getParent()\n");
        exit(1);
    }
    return (G->p[u]);
}

//getDiscover()
//Returns the discover time of a vertex u in the DFS forest
//Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u) {
    if( u < 1 || u > getOrder(G) ){
        printf("Graph Error: u is outside the range of vertices for getDiscover()\n");
        exit(1);
    }
    return (G->d[u]);
}

//getFinish()
//Returns the finish time of a vertex u in the DFS forest
//Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u) {
    if( u < 1 || u > getOrder(G) ){
        printf("Graph Error: u is outside the range of vertices for getFinish()\n");
        exit(1);
    }
    return (G->f[u]);
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

//visit()
//Helper function for DFS to discover nodes
void visit(Graph G, List *S, int x, int *time) {
    G->color[x] = 'g';
    G->d[x] = ++(*time);
    
    if (isEmpty(G->adj[x])) {
        G->color[x] = 'b';
        insertAfter(*S, x);   //Push finished vertex onto the stack

        G->f[x] = ++(*time);
        return;
    }
    
    else {
    moveFront(G->adj[x]);
    while (index(G->adj[x]) != -1) {    //for all y in adj[x]
        int y = get(G->adj[x]);
        if (G->color[y] == 'w') {
            G->p[y] = x;
            visit(G, S, y, time);
        }
        moveNext(G->adj[x]);
    }
        G->color[x] = 'b';
        insertAfter(*S, x);   //Push finished vertex onto the stack

        G->f[x] = ++(*time);
    }
}

//DFS()
//Performs DFS on a source vertex, producing a DFS forest
//Pre: length(S) == getOrder(G)
void DFS(Graph G, List S) {
    if(length(S) != getOrder(G) ){
        printf("List Error: The length of S does not equal the order of the graph.\n");
        exit(1);
    }
    
    //Reinitialize DFS, in case of repeated calls
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = 'w';
        G->p[i] = NIL;
    }
    
    int time = 0;           //local variable time
    int *pt = &time;        //a pointer to pass time to visit()
    List *pS = &S;
    moveBack(S);            //Set up cursor to maintain stack
    
    //for all vertices
    for (int i = 1; i <= getOrder(G); i++) {
        int x = front(S);
        if (G->color[x] == 'w') {
            visit(G, pS, x, pt);
            deleteFront(S);
        }
        else {
            deleteFront(S);
            if (index(S) == -1 && !isEmpty(S)) { //if cursor became undef after deleting front
               moveFront(S);
            }
        }
    }
}

//

// Other functions ---------------------------------------------------------------
//transpose()
//Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G) {
    Graph T = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(T); i++) {
        if (isEmpty(G->adj[i])) {
            continue;
        }
        else {
            moveFront(G->adj[i]);
            
            while (index(G->adj[i]) != -1) {
                int x = get(G->adj[i]);     //access the element in G's adj
                append(T->adj[x], i);
                moveNext(G->adj[i]);        //get next element
            }
        }
    }
    return T;
}

//copyGraph()
//Returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G) {
    Graph C = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(C); i++) {
        if (isEmpty(G->adj[i])) {
            continue;
        }
        else {
            moveFront(G->adj[i]);
            
            while (index(G->adj[i]) != -1) {
                int x = get(G->adj[i]);     //access the element in G's adj
                append(C->adj[i], x);
                moveNext(G->adj[i]);        //get next element
            }
        }
    }
    return C;
}

//printGraph()
//Prints out the graph
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}




