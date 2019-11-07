###########################
# Lab 5: ASCII Binary to Decimal
# CMPE 012 Summer 2018
#
# Nichole Boothroyd 
# nboothro
#
# Language:        MIPS32
#
# Description:     A program outputting taking in an 8-bit binary number from the program argument in the form of a string
#                  and converts it to hex and decimal. 
#
# Notes:           This program is intended to be run from the MARS IDE.

###########################
# Pseudo-Code
#
# Display first prompt
# Save the program argument for later use in myreg
# Print the program argument as a string
# Initilize variables for looping through program argument and memory offset
# For each bit in the program argument
#     load one byte and subtract 48 to convert from ASCII to int
#     if this is the first value
#         do nothing
#     else
#         bitshift $s0 by 1 space
#     Add the int value to $s0
#     Update loop/memory offset counter
# If the first byte in the program argument was 1
#     Sign extend the value in $s0
# Display second prompt
# Initilize bitmask and shift amounts for isolating bits for hex conversion
# For each 4 bits in $s0
#     If value is <= 9
#        Add 48 to get numerical ASCII hex digit 
#     Else if value is >= 10
#        Add 55 to get alpha ASCII hex digit
#     Print hex digit
#     Update bitmask and shift amount values
# Display third prompt
# If first byte of program argument is 1
#     Print "-" character
#     Convert negative number from 2SC
# Store the binary value from $s0 into array
# Load the first byte of this binary number into $t7
# Save the address of the top of the stack
# While $t7 != 0
#     Mod the value in $t7 by 10 to get least significant digit
#     Push this digit onto the stack
#     Move stack pointer down
#     Divide $t7 by 10 to move to next significant digit
# While the stack pointer is not back at it's original position
#     Load the digit from the stack
#     Move stack pointer up
#     Add 48 to get from int to ASCII character
#     Print character
# Print last newline character
# Exit program syscall

     
     
###########################
# Register Usage:
# $t0: Used to store register addresses
# $t1: Variable for bitshift amount
# $t2: Looping variable
# $t3: Bitmask variable for hex conversion
# $t4: Used to store remainder for decimal conversion
# $t7: Variable for manipulating the current bits/data
# $v0: Used to set type of syscall
# $a0: Register used in syscall
# $s0: Register used to save 32-bit sign-extended integer

###########################
# Data declarations
.data 

new_line: .asciiz  "\n"
prompt:   .asciiz  "You entered the binary number:\n"
prompt_2: .asciiz  "The hex representation of the sign-extended number is:\n0x"
prompt_3: .asciiz  "The number in decimal is:\n"
myreg:    .align   2 
          .space   8
array:    .byte    8 

###########################
# Program 
.text 

# Display first prompt
la   $a0  prompt
li   $v0  4
syscall

# Load the address of argv[0] into $a0 for print syscall
lw   $a0 ($a1)
sw   $a0  myreg
syscall
la   $a0  new_line
syscall

#Initialize looping/offset variable
li   $t2  0
la   $t0  array

#Loop through the string and convert chars to ints
loop:
lw   $a0  myreg
add  $a0  $a0  $t2
lbu  $t7 ($a0)
subi $t7  $t7  48

bnez $t2  shift_s0
return:
add  $s0  $s0  $t7

#update loop/offset counter
addi $t2  $t2   1
bleu $t2  7     loop

#Check if first bit is a 1 for sign extension
lw   $a0  myreg
lbu  $t7 ($a0)
subi $t7  $t7   48
bnez $t7  sign_extend
return2:

# Display second prompt
la   $a0  new_line
li   $v0  4
syscall
la   $a0  prompt_2
syscall

#Print integer in hex

# Initialize looping/bitmask variable
li    $t2  0
li    $t3  0xf0000000
li    $t1  28
hex_loop:
and   $t7  $s0  $t3
bne   $t2  7    hex_shift
return3:
# Handle conversion of numerical or alpha digits separately
ble   $t7  9    hex_num
addi  $t7  $t7  55
return_hex_num:

la    $a0  ($t7)
li    $v0   11
syscall

# update loops/counter
addi  $t2  $t2  1
srl   $t3  $t3  4
subi  $t1  $t1  4
ble   $t2  7    hex_loop

# Display third prompt
la   $a0  new_line
li   $v0  4
syscall
syscall
la   $a0  prompt_3
syscall

# Print integer in decimal
lw   $a0  myreg
lbu  $t7  ($a0)
#Print a "-" if the first digit is a 1
beq  $t7  49    print_minus
return4:

sw   $s0  array
lb   $t7  array

# Initialize top of stack address
la   $t0  ($sp)
# Extract each decimal digit and push onto stack
extract:
rem  $t4  $t7  10
subi $sp  $sp  4
sw   $t4  ($sp)
div  $t7  $t7  10
bnez $t7  extract

# Pop from stack to print decimal string
print_dec:
lw   $t7 ($sp)
addi $sp  $sp  4
addi $t7  $t7  48

la   $a0  ($t7)
li   $v0  11
syscall
bne  $sp  $t0  print_dec

li   $v0 4
la   $a0 new_line
syscall

# exit program
li   $v0  10
syscall



## Function to bitshift $s0
shift_s0: 
sll  $s0   $s0 1
b    return

##Function for sign extension
sign_extend:
ori   $s0  $s0 0xffffff00
b     return2

##Function for hex bitshift
hex_shift:
srlv  $t7  $t7 $t1
b     return3

##Function for converting hex numerals
hex_num:
addi  $t7  $t7 48
b     return_hex_num

##Function for printing a dash for negative numbers
print_minus:
li   $a0   45
li   $v0   11
syscall
# 2SC Conversion
not  $s0  $s0
addi $s0  $s0  1
b    return4
