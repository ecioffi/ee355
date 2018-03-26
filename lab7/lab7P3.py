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

	def writeNodeInfo(self, node, file):
		#node.word + '\t' + str(self.totalFrequency[node.word]) + '\t' 
		file.write(node.fileName + '(' + str(node.frequency) + "): ")
		file.write(", ".join(map(str, node.positions)))

	def writeStrings(self, fileName):
		self.listOfDocumentNode.sort(key=lambda node : node.word)

		file = open(fileName, "w")
		nodeIter = iter(self.listOfDocumentNode)
		for node in nodeIter:
			file.write(node.word + '\t' + str(self.totalFrequency[node.word]) + '\t')
			self.writeNodeInfo(node, file)

			nextNode = next(nodeIter, None)
			while nextNode != None and nextNode.word == node.word:
				file.write('\t')
				self.writeNodeInfo(nextNode, file)
				nextNode = next(nodeIter, None)

			file.write('\n')

		file.close()

PI = PositionalIndex()

if len(argv) < 2:
	print("USAGE: python3", argv[0], "FILE1 ...")
	exit()

for arg in enumerate(argv[1:], start=1):
	file = open(arg[1])
	lines = file.read()
	file.close()

	for pos, word in enumerate(filter(None, re.split("[ \t\n]+", lines)), start=1):
		PI.add(arg[1], word, pos)

	PI.writeStrings("out3.txt")