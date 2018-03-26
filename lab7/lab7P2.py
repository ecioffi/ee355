from sys import argv
import re

class DocumentNode:
	def __init__(self, fileName, word, position):
		self.fileName = fileName
		self.word = word
		self.frequency = 1
		self.positions = [position]

class PositionalIndex:
	def __init__(self):
		self.listOfDocumentNode = []
		self.totalFrequency = {}

	def add(self, fileName, word, position):
		for node in self.listOfDocumentNode:
			if (node.word == word) and (node.fileName == fileName):
				node.positions.append(pos)
				node.frequency += 1
				self.totalFrequency[word] += 1
				return
		self.listOfDocumentNode.append(DocumentNode(fileName, word, position))
		if word in self.totalFrequency:
			self.totalFrequency[word] += 1
		else:
			self.totalFrequency[word] = 1

	def writeStrings(self, fileName):
		file = open(fileName, "w")
		for node in self.listOfDocumentNode:
			file.write(node.word+'\t'+str(self.totalFrequency[node.word])+'\t'+node.fileName+'('+str(node.frequency)+") :")
			file.write(", ".join(map(str, node.positions))+'\n')
		file.close()

if len(argv) != 2:
	print("USAGE: python3", argv[0], "FILE")
	exit()

file = open(argv[1])
lines = file.read()
file.close()

PI = PositionalIndex() 

for pos, word in enumerate(filter(None, re.split("[ \t\n]+", lines)), start=1):
	PI.add(argv[1], word, pos)

PI.writeStrings("out2.txt")