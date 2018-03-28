from sys import argv
import numpy as np

if len(argv) < 2:
	print("USAGE: python3", argv[0], "FILE")
	exit()

file = open(argv[1])
lines = file.read()
file.close()

m2 = []
for line in lines.split("\n"):
	if line == '':
		m1 = m2
		m2 = []
		continue
	row = []
	for num in line.split(" "):
		row.append(int(num))
	m2.append(row)

def IOU(m1, m2):
	intersection = np.logical_and(m1, m2)
	union = np.logical_or(m1, m2)
	return intersection.sum() / union.sum()

print("IOU of input matrices is:", IOU(m1, m2))
