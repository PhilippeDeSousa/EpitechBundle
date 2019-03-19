#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
import os

def printMatrix(Matrix, size):
	for x in range(size):
		for y in range(size):
			print(Matrix[x][y], end = "")
			if y < size - 1:
				print(end = " ")
		print()

def firstMatrix(Matrix, Left, Right, NameList):
	size = len(NameList)
	defx = 0
	defy = 0
	for tmp in range(0, len(Left)):
		for x in range(0, size):
			if Left[tmp] == NameList[x]:
				defx = x
		for y in range(0, size):
			if Right[tmp] == NameList[y]:
				defy = y;
		Matrix[defx][defy] = 1
		Matrix[defy][defx] = 1
	printMatrix(Matrix, size)

def secondMatrix(Matrix, Left, Right, NameList, Max):
	size = len(NameList)
	defx = 0
	y = 0
	for x in range(size):
		for y in range(size):
			Lowest = []
			if NameList[x] != NameList[y]:
				findConnection(NameList[x], NameList[y], 0, Left, Right, len(Left) + len(Right), Lowest)
				findConnection(NameList[x], NameList[y], 0, Right, Left, len(Left) + len(Right), Lowest)
				if min(Lowest) <= Max:
					Matrix[x][y] = min(Lowest)
					Matrix[y][x] = min(Lowest)
	printMatrix(Matrix, size)

def findConnection(First, Sec, Count, LeftNames, RightNames, Max, Lowest):
	if Count >= Max:
		print("degree of separation between ", First, " and ", Sec, ": -1", sep="")
		sys.exit(0)
	for tmp in range(0, len(LeftNames)):
		if LeftNames[tmp] == First:
			if RightNames[tmp] == Sec:
				Count += 1
				Lowest.append(Count)
				return Count;
			else:
				findConnection(RightNames[tmp], Sec, Count + 1, LeftNames, RightNames, Max, Lowest)
				findConnection(Sec, RightNames[tmp], Count + 1, LeftNames, RightNames, Max, Lowest)
	return Count

def setMatrix(Names, NameList):
	leftNames = []
	rightNames = []
	size = len(NameList)

	for i in range(0, len(Names)):
		if i % 2 == 0:
			leftNames.append(Names[i])
		else:
			rightNames.append(Names[i])
	Matrix = [[0 for x in range(size)] for y in range(size)]

	print()
	firstMatrix(Matrix.copy(), leftNames, rightNames, NameList);
	print()
	secondMatrix(Matrix.copy(), leftNames, rightNames, NameList, int(sys.argv[2]));


def singleConnection(Names, NameList):
	first = sys.argv[2]
	sec = sys.argv[3]
	leftNames = []
	rightNames = []
	size = len(NameList)

	for i in range(0, len(Names)):
		if i % 2 == 0:
			leftNames.append(Names[i])
		else:
			rightNames.append(Names[i])
	if first not in NameList or sec not in NameList:
		print("degree of separation between ", first, " and ", sec, ": -1", sep="")
	elif first == sec:
		print("degree of separation between ", first, " and ", sec, ": 0", sep="")
	else:
		Lowest = []
		findConnection(first, sec, 0, leftNames, rightNames, len(Names), Lowest)

		print("degree of separation between ", first, " and ", sec, ": ", min(Lowest), sep="")

def checkArgs():
	nb = len(sys.argv)
	nbLinks = 0
	if nb < 3 or nb > 4:
		sys.exit(84)
	if nb == 3:
		try:
			nbLinks = int(sys.argv[2])
		except ValueError:
			print("Error: invalid number.")
			sys.exit(84)
		if nbLinks < 0:
			print("Error: negative number.")
			sys.exit(84)
	try:
		path = sys.argv[1]
		open(path)
	except IOError:
		print("Error : no such file or directory")
		sys.exit(84)
	if os.stat(path).st_size == 0:
		print ("Error : empty file.")
		sys.exit(84)

def main():
	checkArgs()
	names = []
	file = open(sys.argv[1], 'r')
	content = file.read()
	content = content.split('\n')
	for string in content:
		if string :
			names.append(string.split(" is ")[0])
			names.append(string.split(" with ")[1])
	matrixNames = names
	names = list(set(names))
	names.sort()
	if len(sys.argv) == 3:
		for line in names:
			print(line)
		setMatrix(matrixNames, names)
	if len(sys.argv) == 4:
		singleConnection(matrixNames, names)

if __name__ == "__main__":
	main()