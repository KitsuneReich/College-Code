------------------------
Lab 4: Leap in MIPS
CMPE 012 Summer 2018

Boothroyd, Nichole
nboothro
-------------------------

The text of your prompt (“Please input the start year:” and “Please input the end year:”) is stored in the processor’s memory. After assembling your program, what is the range of addresses in which this string is stored?

These strings are stored in memory between 0x10010000 to 0x10010034.

What were the learning objectives of this lab?

This was an introduction to the MIPS ISA: learning how to do basic commands such as printing to the screen, setting variables, and arithmetic operations. Probably also learning how much of the "heavy lifting" is done by compilers in other higher level languages that we kind of take for granted. In addition, this was also an introduction into using the MARS IDE and an opportunity to learn the resources available in the IDE and familiarizing ourselves with error messages and debugging.

Did you encounter any issues? Were there parts of this lab you found enjoyable?

No issues really, this was very straightforward. I think I initially tried to use syscall 51 which provided an input dialog window, lol. I think it's enjoyable/important for CS students to learn that it's not WHICH language you know, but that you understand the core principles of programming. Having already written the leap year finder in C, it's not difficult to translate that to MIPS. This can be very encouraging!

How would you redesign this lab to make it better?

I guess I would just reiterate the comment above to students? I thought it was already SUUUPER kind of Miss Rashkin to provide her branch_test.asm to the students. Being able to translate between programming languages is such an empowering skill! It's not about knowing how to make a for loop in C or Java, but that you understand how a for loop works. Everything else from there is syntactical sugar.  