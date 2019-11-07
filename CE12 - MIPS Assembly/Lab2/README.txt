------------------------
LAB 2: Intro to Logic Simulation
CMPE 012 Summer 2018

Boothroyd, Nichole
nboothro
-------------------------

Part B Truth Table:

in_0 in_1 in_2 | a0 a1 b0 b1 c0 c1 d0 d1 e0 e1 f0 f1 g0 g1
----------------------------------------------------------
0    0    0    | 1  1  1  1  1  1  1  1  1  1  1  1  0  0
0    0    1    | 0  0  1  1  1  1  0  0  0  0  1  1  1  1
0    1    0    | 1  1  1  1  0  0  1  1  1  1  0  0  1  1
0    1    1    | 1  1  0  0  1  1  1  1  1  1  1  1  1  1
1    0    0    | 0  0  1  1  1  1  0  0  0  0  0  0  0  0
1    0    1    | 1  1  0  0  1  1  1  1  0  0  1  1  1  1
1    1    0    | 1  1  1  1  1  1  1  1  0  0  0  0  1  1
1    1    1    | 1  1  1  1  1  1  0  0  0  0  0  0  0  0


Part C Truth Table:

in_0 in_1 in_2 | out_0 out_1 out_2 out_3 out_4 out_5 out_6 out_7
----------------------------------------------------------------
0    0    0    |   1     0     0     0     0     0     0     0
0    0    1    |   0     0     0     0     1     0     0     0
0    1    0    |   0     0     1     0     0     0     0     0
0    1    1    |   0     0     0     0     0     0     1     0
1    0    0    |   0     1     0     0     0     0     0     0
1    0    1    |   0     0     0     0     0     1     0     0
1    1    0    |   0     0     0     1     0     0     0     0
1    1    1    |   0     0     0     0     0     0     0     1

What did you learn in this lab?

I learned not only how to use the Multimedia Logic Software, but also how to translate
the information from a truth table into a Karnaugh map. After getting the K-map in place,
I worked towards finding the simplest pattern in order to create logic gates that satisfy
the original truth table.

What worked well? Did you encounter any issues?

The template provided for MML was helpful and learning the keyboard shortcuts to speed
up my workflow was extremely helpful. I'm not confident my logic diagrams are properly
commented, though. Initially, I believe I used A-G in one big K-map instead of creating a
separate map for each LED, but was able to use this just fine once I got A up and running.
I was a little confused at first with the extra inputs needed for Part A's 7-segment
display, but if this was to teach us to use switches/inputs then I understand. 

How would you redesign this lab to make it better?

I don't really think I have the pedagogical knowledge to comment on this. Physical LED's and circuits would be awesome, but also makes the lab generally more inaccessible and probably nigh impossible to grade.