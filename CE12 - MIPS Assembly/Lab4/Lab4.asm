# Lab 4: Leap in MIPS
# CMPE 012 Summer 2018
#
# Nichole Boothroyd 
# nboothro
#
# Language:        MIPS32
#
# Description:     A program outputting leap years from user input ranges. 
#
# Notes:           This program is intended to be run from the MARS IDE.

###########################
# Pseudo-Code
#
#  Prompt user for starting year
#  Initialize a to input
#  Prompt user for ending year
#  Initialize b to input
#  for each value between a and b
#     if value is divisible by 4 AND 100 AND 400
#          print leap
#     else if value is divisible by 4 AND NOT divisible by 100
#          print leap
#     else
#         print the value
#  exit program

###########################
# Register Usage:
#
# $t0: Start year
# $t9: End year
# $t1: Looping variable
# $t2: Remainder variable
# $v0: used to set type of syscall
# $a0: register used in syscall

###########################
# Data declarations
.data 

in_prompt: .asciiz "Please input the start year: " 
end_prompt: .asciiz "Please input the end year: "
new_line: .asciiz "\n"
print_leap: .asciiz "leap"


###########################
# Program 
.text 

#display the input prompt to the user
li $v0 4
la $a0 in_prompt
syscall 

#Read integer input from user
li $v0 5
syscall

#Copy the read integer from $v0 into $t0 for later use
la $t0 ($v0)


#Display the input prompt to the user
li $v0 4
la $a0 end_prompt
syscall

#Read integer input from user
li $v0 5
syscall

#Copy the read integer from $v0 into $t9 for later use
la $t9 ($v0)

#Initialize looping variable to start year
la $t1 ($t0)



#Loop for checking each year
loop:

#check to see if divisible by 4: If so, check 100
rem $t2 $t1 4
beqz $t2 check_100

print_year:
#print year
li $v0 1
la $a0 ($t1)
syscall

return:
#print newline
li   $v0 4
la   $a0 new_line
syscall

#increment year
addiu $t1 $t1 1
#loop back 
bleu $t1 $t9 loop

# exit program
li   $v0 10
syscall





########################
check_100:

#Check to see if divisible by 100
rem $t2 $t1 100

#If divisible by 4 AND 100: check 400
beqz $t2 check_400

#If divisible by 4 AND NOT divisible by 100: print leap
bnez $t2 leap

########################
check_400:

#If divisible by 4 AND 100 AND 400: Print leap
rem $t2 $t1 400
beqz $t2 leap

#Else, return to print year
bnez $t2 print_year


########################
leap:

#Printing the string "leap"
li $v0 4
la $a0 print_leap
syscall
b return