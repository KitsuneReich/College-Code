//Nichole Boothroyd    cruzID: nboothro  Assignment: pa2
//-----------------------------------------------------------------------------
// FileIO.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
    
    int n, count=0;
    FILE *in, *out;
    char line[MAX_LEN];
    char tokenlist[MAX_LEN];
    char* token;
    
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
    
    /* read each line of input file, then count and print tokens */
    char strs[MAX_LEN][MAX_LEN];
    List L = newList();

    
    while( fgets(line, MAX_LEN, in) != NULL)  {
        count++;
        n = 0;
        token = strtok(line, " \n");
        tokenlist[0] = '\0';
        while( token!=NULL ){
            strcat(tokenlist, "   ");
            strcat(tokenlist, token);
            strcat(tokenlist, "\n");
            n++;
            token = strtok(NULL, " \n");
        }
        strcpy(strs[count - 1], tokenlist);
        
        
 //       fprintf(out, "line %d contains %d token%s: \n", count, n, n==1?"":"s");
 //       fprintf(out, "%s\n", tokenlist);
    }
    
    for(int i = 0; i<= count; i++) {
        if(length(L) == 0) {
            append(L, i);
            //           printf("Inserting first element %d\n", index(L));
            moveFront(L);
            continue;
        }
        
        while (strcmp(strs[index(L)], strs[i]) < 0) { //While index element < new element
            moveNext(L);
            if (index(L) == -1) {
                append(L, i);       //append to the back
                moveFront(L);       //reset index to the front
                break;
            }
        }
        if (strcmp(strs[index(L)], strs[i]) > 0){
            //                printf("Inserting before index %d\n", index(L));
            insertBefore(L, i);
            moveFront(L);
        }
    }
    
    moveFront(L);
    for(int i = 0; i < length(L); i++) {
        fprintf(out, "%s", strs[get(L)]);
        moveNext(L);
    }
    freeList(&L);
    
    /* close files */
    fclose(in);
    fclose(out);
    
    return(0);
}
