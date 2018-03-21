import numpy as np
from scipy import stats
import math

def typify(item):
	try:
		return float(item)
	except ValueError:
		return int(item=='M')

file = open("wdbc.data")
lines = file.readlines()
file.close()

trainData = [list(map(typify, lines[n].split(','))) for n in range(round(len(lines)*.80))]
testData = [list(map(typify, lines[n].split(','))) for n in range(round(len(lines)*.80), len(lines))]

def knn(tumor : list, fields : list, weights : list):
	distance = 0.0
	classDist = []
	for refTumor in trainData:
		for n in fields:
			distance += ((tumor[n] - refTumor[n])**2) * weights[n]
		distance = math.sqrt(distance)
		classDist.append((distance, refTumor[1]))
	classDist.sort(key=lambda x: x[0])

	return int((classDist[0][1] + classDist[1][1] + classDist[3][1]) / 2)

def genWeights():
	weights = range(2, 32)
	totalRight = 0
	for f in range(2, 32):
		right = 0
		for tumor in testData:
			right += knn(tumor, f, [1 for n in range(33)]) == tumor[1]
		weights[f] = right
		totalRight += right
	weights = map(lambda x: float(x/totalRight), weights)
	print(weights)

genWeights()
#print(right, "out of", len(testData), "correct == ", right / len(testData))