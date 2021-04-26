from math import *
import matplotlib.pyplot as plt

def phi(x, k):
	return pow(x, k)

def loadTableXY(nameFile):
	tableXY = [[], [], []]
	with open(nameFile, 'r') as f:
		tmpArr = f.readlines()
	for string in tmpArr:
		tmp = []
		tmp = string.split(" ")
		tableXY[0].append(float(tmp[0]))
		tableXY[1].append(float(tmp[1]))
		tableXY[2].append(float(tmp[2].split("\n")[0]))

	return tableXY

def getCoeffSLAU(tableXY, n):
	slau = []
	column = []

	for k in range(n + 1):
		tmp = 0
		slau.append([0 for m in range(n + 1)])
		for i in range(len(tableXY[0])):
			tmp += tableXY[2][i] * tableXY[1][i] * phi(tableXY[0][i], k)
			for j in range(n + 1):
				tmpCoeff = tableXY[2][i] * phi(tableXY[0][i], k + j)
				slau[k][j] += tmpCoeff
		column.append(tmp)

	return slau, column

def getReverseSLAU(slau):
	sz = len(slau)
	res = []

	for i in range(sz):
		res.append([])
		for j in range(sz):
			if (i == j):
				res[i].append(1.0)
			else:
				res[i].append(0.0)

	for i in range(sz):
		for j in range(sz):
			if (i != j):
				tmp = slau[j][i] / slau[i][i]

				for k in range(sz):
					slau[j][k] -= slau[i][k] * tmp
					res[j][k] -= res[i][k] * tmp

	for i in range(sz):
		for j in range(sz):
			res[i][j] /= slau[i][i]

	return res

def multiplication(slau, column):
	sz = len(slau)
	res = []

	for i in range(sz):
		res.append(0)
		for j in range(sz):
			res[i] += slau[i][j] * column[j]

	return res

def graphic(tableXY, x, y):
	fig = plt.figure()
	plt.scatter(tableXY[0], tableXY[1], label = "исходная таблица", color = "blue")
	plt.plot(x, y, color = "green")
	plt.grid(True)
	plt.legend()
	plt.show()

if (__name__ == "__main__"):
	tableXY = loadTableXY("data.txt")
	# n = 2

	for i in range(len(tableXY)):
		print(tableXY[0][i], tableXY[1][i], tableXY[2][i])

	n = int(input("Введите степень полинома: "))
	while (n <= 0):
		print("Степень полинома должна быть больше 0\n")
		n = int(input("Введите степень полинома: "))

	slau, column = getCoeffSLAU(tableXY, n)
	print(slau, column)
	slau = getReverseSLAU(slau)
	a = multiplication(slau, column)

	print(a)

	distanceX = tableXY[0][-1] - tableXY[0][0] + 1

	stepX = distanceX / 100
	x = []
	y = []

	tmpX = tableXY[0][0] - stepX * 10

	while (tmpX < tableXY[0][-1] + stepX * 10):
		x.append(tmpX)
		tmpY = 0
		for k in range(n + 1):
			tmpY += phi(tmpX, k) * a[k]
		y.append(tmpY)
		tmpX += stepX

	graphic(tableXY, x, y)