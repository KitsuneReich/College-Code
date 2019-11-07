//Nichole Boothroyd     cruzID: nboothro        Assignment: pa5
//
//-----------------------------------------------------------------------------
// FindComponents.c
// Client program utilizing Graph ADT to find connected components from DFS forest
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 160

int main (int argc, char * argv[]) {
    
    FILE *in, *out;
    
    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    int n, a = -17, b = -17;
    fscanf(in,"%d", &n);
    Graph G = newGraph(n);
    Graph T = NULL;
    List S = newList();
    for(int i=1; i<=n; i++) append(S, i);       //initialize S
    fscanf(in,"%d", &a);
    fscanf(in,"%d", &b);
    while (a != 0 && b != 0) {
        addArc(G, a, b);
        fscanf(in,"%d", &a);
        fscanf(in,"%d", &b);
    }
    
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    int k = 0;      //connected components sum
    
    DFS(G, S);
    T = transpose(G);
    DFS(T, S);
    
    moveBack(S);
    while (index(S) != -1) {
        int x = get(S);
        if (getParent(T, x) == NIL) {
            k++;
        }
        movePrev(S);
    }
    
 //   printList(out, S);
    fprintf(out, "\nG contains %d strongly connected components:\n", k);
    moveBack(S);
    int x = get(S);
    int count = 0;

    for (int i = 1; i <= k; i++) {
        fprintf(out, "Component %d:", i);
        while (getParent(T, x) != NIL) {
            movePrev(S);
            x = get(S);
            count++;
        }
        fprintf(out, " %d", x);
        //print out the components
        for (int i = 1; i <= count; i++) {
            moveNext(S);
            x = get(S);
            fprintf(out, " %d", x);
        }
        //Reset back
        for (int i = 1; i <= count; i++) {
            movePrev(S);
        }
        count = 0;
        fprintf(out, "\n");
        movePrev(S);
        if (index(S) != -1) {
            x = get(S);
        }
    }

    
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    
    /* close files */
    fclose(in);
    fclose(out);
    
    return(0);
}
