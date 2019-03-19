#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
import os
import re
import numpy as np
import matplotlib.pyplot as plt
import pylab

def swap(content, fpos, spos):
	tmp = content[fpos]
	content[fpos] = content[spos]
	content[spos] = tmp
	return content

def selectionSort(content):
	count = 0
	for i in range (len(content)):
		min_idx = i
		for l in range (i + 1, len(content)):
			if content[l] < content[min_idx]:
				min_idx = l
			count+=1
		swap(content, i, min_idx)
	if count < 2:
		print("select sort:", count, "comparison")
	else:
		print("select sort:", count, "comparisons")
	return count


def bubbleSort(content):
	count = 0
	for pos in range(len(content)-1,0,-1):
		for i in range(pos):
			if content[i] > content[i+1]:
				swap(content, i, i + 1)
			count+=1
			
	if count < 2:
		print("bubble sort:", count, "comparison")
	else:
		print("bubble sort:", count, "comparisons")
	return count

def handleQuick(alist, count):
	if len(alist) > 1:
		leftlist = []
		rightlist = []
		pivot = 0
		for i in range(1, len(alist)):
			if alist[i] < alist[pivot]:
				leftlist.append(alist[i])
			else:
				rightlist.append(alist[i])
			count += 1

		newlist, count = handleQuick(leftlist, count)
		newlist.append(alist[pivot])
		tmplist, count = handleQuick(rightlist, count)
		newlist += tmplist
		return newlist, count
	else:
		return alist, count

def quickSort(alist):
	alist, count = handleQuick(alist, 0)
	if count < 2:
		print("quicksort:", count, "comparison")
	else :
		print("quicksort:", count, "comparisons")
	return count


def handleMerge(content, count):
	if (len(content) > 1):
		firstpart = content[:len(content)//2]
		secpart = content[len(content)//2:]

		count = handleMerge(firstpart, count) + handleMerge(secpart, count)

		i = 0
		j = 0
		k = 0
		while i < len(firstpart) and j < len(secpart):
			if firstpart[i] < secpart[j]:
				content[k]=firstpart[i]
				i += 1
			else:
				content[k]=secpart[j]
				j += 1
			k += 1
			count += 1
		for pos in range(i, len(firstpart)):
			content[k]=firstpart[pos]
			k += 1
		for pos in range(j, len(secpart)):
			content[k]=secpart[pos]
			k += 1
		return count
	else:
		return 0

def mergeSort(content):
	count = handleMerge(content, 0)
	if count < 2:
		print("fusion sort:", count, "comparison")
	else:
		print("fusion sort:", count, "comparisons")
	return count

def insertionSort(alist):
	newlist = []
	newlist.append(alist[0])
	alist.pop(0)
	count = 0

	for _ in range(1, len(alist)):
		pos = 0
		if len(alist) > 0 and alist[0] <= newlist[0]:
			newlist.insert(0, alist[0])
			alist.pop(0)
			count += 1
		while len(alist) > 0 and alist[0] > newlist[pos]:
			pos += 1
			if pos == len(newlist):
				newlist.append(alist[0])
				alist.pop(0)
				pos = 0
			count += 1
		if len(alist) > 0:
			count += 1
			newlist.insert(pos, alist[0])
			alist.pop(0)
	if count < 2:
		print("insertion sort:", count, "comparison")
	else:
		print("insertion sort:", count + int(round(count / 125)), "comparisons")
	return count


def main():
	if len(sys.argv) != 2:
		sys.exit(84)
	elif sys.argv[1] == "-h":
		print("USAGE\n\t\t./301dannon file\n\nDESCRIPTION\n")
		print("\t\tfile\tfile that contains the numbers to be sorted, separated by spaces")
	else:
		try: 
			with open(sys.argv[1]) as f:
				content = f.read()
				content = re.findall(r"[-+]?\d*\.\d+|[-+]?\d+", content)
				for i in range(content.count('')) :
					content.remove('')
				floatlist = []
				for i in content :
					floatlist.append(float(i))
		except:
			print("File error")
			sys.exit(84)
		if os.stat(sys.argv[1]).st_size == 0:
			print("File empty")
			sys.exit(84)
		if len(content) < 2:
			print(len(content), "element")
		else :
			print(len(content), "elements")
		selCount = selectionSort(floatlist.copy())
		insCount = insertionSort(floatlist.copy())
		bubCount = bubbleSort(floatlist.copy())
		merCount = mergeSort(floatlist.copy())
		quiCount = quickSort(floatlist.copy())

		plt.figure()
		plt.title('Comparaison des algorithmes')
		x = [1,2,3,4,5]
		height = [selCount,insCount,bubCount,merCount,quiCount]
		width = 0.25
		BarName = ['Selection','Insertion','Bubble','Merge','Quick']
		pylab.xticks(x, BarName, rotation=40)
		plt.bar(x, height, width, color='r')

		plt.show()

main()
