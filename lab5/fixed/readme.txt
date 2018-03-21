brokengdb1:
I set a breakpoint at line 22 where "result" was changed and printed its value every iteration in the while loop. I saw that it was going to zero at the last iteration. To fix the bug I changed line 22 to "result*=n+1"

brokengdb2:
I stepped through the program, and I saw that the do-while loop was getting exited every time after one iteration. I then noticed that the condition had a ">" instead of a "<." Switching to the proper symbol fixed the bug.

brokengdb3:
I ran the program in gdb, which identified the segfault as coming from the next() function, which the backtrace showed was called in the remove function. Analasys of the remove function revealed three serious bugs in its implementation:
1) on line 57, head was being set to a newly constructed Node instead of the existing Node in the list
2) on line 64 temp was being deleted instead of marker
3) on line 69 marker was being set to 0 for no reason

crash1::
It segfaults because memory for the pointer is not allocated.

crash2:
The program crashes with a floating point exception. GDB shows that it occurs at line 11. Cursory inspection shows that the program tries to divide be zero at this line, which is impossible, hence the exception.

stepcheck:
It seems to work. I tested all the functionality repeatedly.