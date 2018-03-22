# cancer dataset from UCI -- http://archive.ics.uci.edu/ml/datasets/Breast+Cancer+Wisconsin+%28Diagnostic%29

import math

def typify(item):
	try:
		return float(item)
	except ValueError:
		return int(item=='M')

print("Loading tumors...")
file = open("wdbc.data")
lines = file.readlines()
file.close()
print(len(lines), "Tumors loaded. Splitting 80/20 percent into training/testing data.")

trainData = [list(map(typify, lines[n].split(','))) for n in range(round(len(lines)*.80))]
testData = [list(map(typify, lines[n].split(','))) for n in range(round(len(lines)*.80), len(lines))]

print("Testing based on 3 NN...")
def knn(tumor : list, wFields = list(zip(range(2, 32), [1 for n in range(2, 32)]))):
	distance = 0.0
	classDist = []
	for refTumor in trainData:
		for wf in wFields:
			distance += ((tumor[wf[0]] - refTumor[wf[0]])**2) * wf[1]
		distance = math.sqrt(distance)
		classDist.append((distance, refTumor[1]))
	classDist.sort(key=lambda x: x[0])
	return int((classDist[0][1] + classDist[1][1] + classDist[3][1]) / 2)

right = 0
for tumor in testData:
			right += knn(tumor) == tumor[1]
print(right, "/", len(testData), "testing tumors classified as benign or malignant correctly;", '%.2f' % (right / len(testData)), "success rate")