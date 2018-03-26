from sys import argv
import re

if len(argv) != 2:
	print("USAGE: python3", argv[0], "FILE")
	exit()

file = open(argv[1])
lines = file.read()
file.close()

words = []
positions = []

for pos, word in enumerate(filter(None, re.split("[ \t\n]+", lines)), start=1):
	if word in words:
		positions[words.index(word)].append(pos)
	else:
		words.append(word)
		positions.append([pos])
strings = list(zip(words, positions))

file = open("out1.txt", "w")

for index, word in enumerate(words):
	file.write(words[index] + " ")
	file.write(", ".join(map(str, positions[index]))+"\n")

file.close()