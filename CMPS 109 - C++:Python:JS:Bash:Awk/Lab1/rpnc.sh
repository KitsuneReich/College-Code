# ---------------------------------------------------------------------------------
#  LAB 1: Reverse Polish Notation (RPN) Calculator
#  CMPS 109  Spring 2018 University of California Santa Cruz
# 
#  Boothroyd, Nichole
#  nboothro
# 
#  Language:    Bash
#  
#  Description: This program accepts a single string argument in RPN, evaluates it,
#               and prints the answer to stdout.
# 
#  Usage:       /rpnc.sh "RPN expression"
# 
# ---------------------------------------------------------------------------------

arg=`echo "$1" | sed 's/\*/K/g'`                #Replace troublesome * with K
index=0
declare -a stack

for word in $arg                                #For each word in the argument:
do
if [[ "$word" =~ ^[0-9]+$ ]]                    #If it is a number. . .
    then
        stack[$index]=$word                     #push to the stack
        ((index += 1))                          #increment stack index
    else
        ((i_1 = index - 2))                     #If it's not a number. . .
        ((i_2 = index - 1))                     #Get indices for popping stack
        ((index -= 2 ))
        ((result = -17))                        #Dummy value -17

        op_2=${stack[$i_2]}                     #Get values from popping stack
        op_1=${stack[$i_1]}
        if [[ "$word" == "+" ]]                 #Evaluate based on operator:
        then
            result=$((op_1 + op_2))
        fi
        if [[ "$word" == "-" ]]
        then
            result=$((op_1 - op_2))
        fi
        if [[ "$word" == "/" ]]
        then
            result=$((op_1 / op_2))
        fi
        if [[ "$word" == "K" ]]
        then
            result=$((op_1 * op_2))
        fi
        if [[ "$word" == "^" ]]
        then
            result=$((op_1 ** op_2))
        fi

        stack[$index]=$result                   #Push result onto stack
        ((index += 1))
    fi
done
echo $stack                                     #Print final result: stack[0]
