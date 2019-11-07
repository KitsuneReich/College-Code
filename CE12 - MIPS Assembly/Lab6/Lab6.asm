####################################################################################
# Created by:  Boothroyd, Nichole
#              nboothro
#              7 August 2018
#
# Assignment:  Lab 6: Musical Subroutines
#              CMPE 012, Computer Systems and Assembly Language
#              UC Santa Cruz, Summer 2018
# 
# Description: This program prints plays musical notes based on string input.
# 
# Notes:       To be used with the MARS IDE. 
####################################################################################

#---------------
# REGISTER USAGE
# a0:  Program arguments
# a1:  Program arguments
# v0:  Return values
# v1:  Return values
# s0:  Used for accessing/manipulating bytes of memory
# s2:  Used for volume control
# s3:  Used for duration control
# s4:  Holds 60,0000 for tempo calculations
# s5:  Used for tempo calculations
# s6:  Used to hold value of one beat after tempo is calculated
# t0:  Used for counting # of notes in get_song_length. 
# t1:  Used for byte access in get_song_length. Elsewhere, used for holding rhythm value.
# t4:  Looping variable for play_song. 
# t5:  Holds length of the song. 
# t7:  Used to access pitch value from $v0.
# t8:  Used to access rhythm value from $v0.
# sp:  Used to manipulate stack pointer.

################
# Program data
.data 

mySong:    .asciiz "e'8 g' e'' c'' d'' g''"
reg_v:     .align   2
           .space   4

################
# Program
.text

play_song:
# input:  $a0 - address of first character in string containing song
#         $a1 - tempo of song in beats per minute
la    $s5  ($a1)
li    $s4   60000
#60,0000 ms div by tempo
div   $s6   $s4     $s5  
subi  $sp   $sp     4
sw    $ra  ($sp)
jal   get_song_length
lw    $ra  ($sp)
addi  $sp   $sp     4

la    $t5  ($v0)
la    $v1   song
song_loop:
subi  $sp   $sp     4
sw    $ra  ($sp)
jal   play_note
lw    $ra  ($sp)
addi  $sp   $sp     4
addi  $t4   $t4     1
blt   $t4   $t5     song_loop

#exit play_song
jr    $ra

get_song_length:
li    $t0   0
loop:
lb    $t1  ($a0)
addi  $a0   $a0     1
#if it's not a space, loop; if it is a space or the end of file, add 1
beqz  $t1   exit_length
bne   $t1   0x20    loop
addi  $t0   $t0     1
b     loop

exit_length:
addi  $t0   $t0     1
# output: $v0 - number of notes in song
la    $v0  ($t0)
jr    $ra


play_note:

#$a0 - address of first character in string containing note encoding
la    $a0  ($v1)
#$a1 - rhythm of previous note
la    $a1  ($t1)
subi  $sp   $sp     4
sw    $ra  ($sp)
jal   read_note
lw    $ra  ($sp)
addi  $sp   $sp     4

#get pitch from $v0
andi  $t7   $v0     0x0000FFFF
#get rhythm from $v0
andi  $t8   $v0     0xFFFF0000
srl   $t8   $t8     16
beq   $t8   1       whole_note
beq   $t8   2       half_note
beq   $t8   4       note
beq   $t8   8       quarter_note
beq   $t8   16      eighth_note
return_beat:

#pitch
la    $a0  ($t7)
#duration in ms      
la    $a1  ($s3)
#instrument
li    $a2   120
#volume
la    $a3  ($s2)
#syscall for MIDI synchronous
li    $v0   33
syscall 
jr    $ra

read_note:
subi  $sp   $sp     4
sw    $ra  ($sp)
jal   get_pitch

# input:  $a0 - address of character in string containing song encoding after pitch is determined
#         $a1 - previous note rhythm
la    $a0  ($v1)
la    $a1  ($t1)
jal   get_rhythm

lw    $ra  ($sp)
addi  $sp   $sp     4

#return to play_note
# output: $v0 - note rhythm in bits [31:16], note pitch in bits [15:0]
#         $v1 - address of first character of what would be next note
lw    $v0   reg_v
la    $v1   ($a0)
jr    $ra

get_pitch:

lb    $s0   ($a0)
beq   $s0    0x72   rest
#subtract from hex value to decimal MIDI value
subi  $s0    $s0    37
li    $s2    64
return_1:
return_2:
return_3:
return_4:
return_5:
addi  $a0    $a0    1
#get next char
lb    $s1   ($a0)
  
beq   $s1    0x27   raise_oct
beq   $s1    0x2C   lower_oct
beq   $s1    0x65   flatten
beq   $s1    0x69   sharpen
beq   $s1    0x20   exit_pitch

#if $s1 isn't any of the values above, it must be a number for the rhythm
bge   $s1    0x31   exit_pitch

#store value
#output: $v0 - MIDI pitch value
#        $v1 - address of character after pitch is determined
exit_pitch:
sb    $s0    reg_v
move  $v0    $s0
move  $v1    $a0

#return to read_note
jr    $ra

get_rhythm:
lb    $t1   ($a0)
#subtract to get int
subi  $t1    $t1    48
blt   $t1    1      prev_rhythm

addi  $a0    $a0    2
la    $v0   ($t1)
exit_rhythm:
#return to read_note
sb    $t1   reg_v+2
la    $v1   ($a0)
jr    $ra

exit:
# exit program
li    $v0    10
syscall

##############
#Rests for a beat 
rest:
li    $s2    0
b     return_5

##############
#Raises an octave 
raise_oct:
addi  $s0    $s0    12
b     return_1

##############
#Lowers an octave 
lower_oct:
subi  $s0    $s0    12
b     return_2

##############
#Flattens note
flatten:
subi  $s0    $s0    1
#no need to check "s"  in es, move address
addi  $a0    $a0    1
b     return_3

##############
#Sharpens note 
sharpen:
addi  $s0    $s0    1
#no need to check "s"  in is, move address
addi  $a0    $a0    1
b     return_4

##############
#If no new rhythm to set, use previous
prev_rhythm:
la    $v0   ($a1)
addi  $a0    $a0    1
b     exit_rhythm

##############
#If rhythm == 1
whole_note:
mul   $s3    $s6    4
b     return_beat

##############
#If rhythm == 2
half_note:
mul   $s3    $s6    2
b     return_beat

##############
#If rhythm == 4
note:
la    $s3   ($s6)
b     return_beat

##############
#If rhythm == 8
quarter_note:
div   $s3    $s6    2
b     return_beat

##############
#If rhythm == 16
eighth_note:
div   $s3    $s6    4
b     return_beat