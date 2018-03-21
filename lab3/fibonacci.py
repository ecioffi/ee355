from random import seed, randint
from subprocess import PIPE, Popen
from time import time

sampleSize = 10000;

seed();
x = [randint(0, 100000) for _ in range(sampleSize)];

t1 = time();
for i in range(sampleSize):
	fibDP = Popen(["./fibonacci_dp", str(x[i])], stdout=PIPE);
	if (int(fibDP.stdout.readline()) == 1):
		print("Congratulations! You have the Fibonacci number", x[i])
	else:
		print("Sorry!", x[i], "is not a Fibonacci number, but the closest Fibonacci number to it is", int(fibDP.stdout.readline()))
t2 = time();

t3 = time();
for i in range(sampleSize):
	fibR = Popen(["./fibonacci_recursive", str(x[i])], stdout=PIPE);
	if (int(fibR.stdout.readline()) == 1):
		print("Congratulations! You have the Fibonacci number", x[i])
	else:
		print("Sorry!", x[i], "is not a Fibonacci number, but the closest Fibonacci number to it is", int(fibR.stdout.readline()))
t4 = time();
print("./fibonacci_dp took", (t2 - t1), "seconds to check", sampleSize, "random numbers ranging from 0 to 100000")
print("./fibonacci_recursive took", (t4 - t3), "seconds to check the same numbers")