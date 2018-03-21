import numpy as np
from scipy import stats

file = open("housingPrice.txt")
years = []
prices = []
for line in file.readlines():
	years.append(int(line.split('\t')[0]))
	prices.append(int(line.split('\t')[1]))
file.close()

slope, intercept, r_value, p_value, std_err = stats.linregress(years, prices)
def linreg(year):
	return intercept + year*slope

p = np.polyfit(years, prices, 2)
def quadreg(year):
	return (p[0]*(year**2) + p[1]*year + p[2])

linvar = 0;
quadvar = 0;
for n in range(len(prices)):
	linvar += (prices[n] - linreg(years[n]))**2
	quadvar += (prices[n] - quadreg(years[n]))**2

def bestreg(year):
	if linvar < quadvar:
		return linreg(year)
	else:
		return quadreg(year)

print("The value of Y if X equals 2015 is predicted to be", bestreg(2015))
print("The value of Y if X equals 10000 is predicted to be", bestreg(10000))