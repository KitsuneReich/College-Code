//Nichole Boothroyd     cruzID: nboothro        Assignment: pa4
//
//-----------------------------------------------------------------------------
// FindPath.c
// Client program utilizing Graph ADT
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

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
    fscanf(in,"%d", &a);
    fscanf(in,"%d", &b);
    while (a != 0 && b != 0) {
        addEdge(G, a, b);
        fscanf(in,"%d", &a);
        fscanf(in,"%d", &b);
    }
    printGraph(out, G);
    
    /* close files */
    fclose(in);
    fclose(out);
    
    return(0);
}
