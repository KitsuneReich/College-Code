------------------------
Lab 5: ASCII Binary to Decimal
CMPE 012 Summer 2018

Boothroyd, Nichole
nboothro
-------------------------

What was your approach to converting the binary number to decimal?
At first I tried doing a similar conversion to hex, with adding the numeric values between chars and ints, but got stuck. The tidbit in lecture about using division and modulus by 10 was extremely helpful. After that, I used a stack to keep the digits in proper order.

What did you learn in this lab?
Mostly, about memory in MIPS. How to access the values I want and where/how they are stored in memory, from program arguments to the stack pointer. Frustratingly, the difference between loading a register's address and inadvertently loading just that register's contents. 

Did you encounter any issues? Were there parts of this lab you found enjoyable?
I totally forgot about checking for hex values <9 and >10. At first, all the values I was checking were A-F, so I didn't even notice there was an issue for a moment. I don't know if I found it enjoyable, but when I was able to use a hex immediate as my bitmask and it worked on the first try, I was filled with joy.

How would you redesign this lab to make it better?
Not really sure on this one. . . I think this was a pretty well rounded lab. Dealing with things in memory is just a little intimidating overall.