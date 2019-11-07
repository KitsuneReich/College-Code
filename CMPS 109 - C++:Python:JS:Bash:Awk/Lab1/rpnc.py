# ---------------------------------------------------------------------------------
#  LAB 1: Reverse Polish Notation (RPN) Calculator
#  CMPS 109  Spring 2018 University of California Santa Cruz
# 
#  Boothroyd, Nichole
#  nboothro
# 
#  Language:    Python3
#  
#  Description: This program accepts a single string argument in RPN, evaluates it,
#               and prints the answer to stdout.
# 
#  Usage:       python rpnc.py "RPN expression"
# 
# ---------------------------------------------------------------------------------

import sys
import re

stack = []
argS = str(sys.argv[1])             #Save argument string
arg = argS.split()                  #Create a list of the words from string

for each in arg:                    #For each word in the list:
    input = str(each)               #Cast as str for isdigit()
    if input.isdigit():             #Is it a number. . .
        stack.append(each)          #. . . Then push to stack
    else:
        op_2 = int(stack.pop())     #Since it's not a number. . .
        op_1 = int(stack.pop())     #. . . Pop from stack
        if input == "+":            #Evaluate based on operator:
            result = (op_1 + op_2)
        if input is "-":
            result = (op_1 - op_2)
        if input is "/":
            result = (op_1 / op_2)
        if input is "^":
            result = (op_1 ** op_2)
        if input is "*":
           result = (op_1 * op_2)
        stack.append(result)        #Push result onto stack

print(stack.pop())                  #Pop final result from stack
