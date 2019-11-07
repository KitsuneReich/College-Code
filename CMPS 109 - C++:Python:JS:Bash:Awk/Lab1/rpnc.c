//---------------------------------------------------------------------------------
// LAB 1: Reverse Polish Notation (RPN) Calculator
// CMPS 109  Spring 2018 University of California Santa Cruz
// 
// Boothroyd, Nichole
// nboothro
//
// Language: C
// 
// Description: This program accepts a single string argument in RPN, evaluates it,
//              and prints the answer to stdout. Returns -1 on error, 0 otherwise.
//
// Usage:       gcc rpnc.c -o rpnc
//	        ./rnpc "RPN expression"
//
//---------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <tgmath.h>

int main(int argc, char *argv[]) {
    int stack[17];
    int sI = 0;                             //stack index
    char * myString = strtok(argv[1], " "); //Pull token off of arg string
    while (myString != NULL)                //Until reaching end of string:
    {
        if (isdigit(*myString)) {           //Check to see if token is a number
            int data = atoi(myString);      //str to int conversion
            stack[sI] = data;               //push onto stack
            sI++;                           //Increment stack index
        }
        else {
            int op_2 = (stack[sI - 1]);     //Since token is not a number. . .
            int op_1 = (stack[sI - 2]);     //Pop values off of stack
            sI -= 2;                        //Update stack index
            int result = -17;               //Dummy value
            
            if (*myString == '+'){          //Evalue based on operator:
                result = (op_1 + op_2);
            }
            else if (*myString == '-'){
                result = (op_1 - op_2);
            }
            else if (*myString == '/'){
                result = (op_1 / op_2);
            }
            else if (*myString == '*'){
                result = (op_1 * op_2);
            }
            else if (*myString == '^'){
                result = (pow(op_1,op_2));
            }
            
            stack[sI] = result;             //push result onto the stack
            sI++;
        }
        myString = strtok (NULL, " ");      //Pull next token off of str
    }

    sI--;                                //"pop" result off the stack
    printf("%d\n", stack[sI]);

    return 0;
}

