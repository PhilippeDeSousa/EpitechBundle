#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
import operator

Time = 0

class TaskClass():
    def __init__(self, _name, _turns, _req):
        self.Name = _name
        self.Turns = int(_turns)
        self.Req = list(_req)
        self.Needs = list(_req)
        self.Interval = (0, 0, 0)

def checkParams():
    if len(sys.argv) != 2:
        print("Error: 2 arguments required")
        sys.exit(84)
    try:
        path = sys.argv[1]
        open(path)
    except IOError:
        print("Error: no such file or directory")
        sys.exit(84)
    if os.stat(path).st_size == 0:
        print ("Error: empty file.")
        sys.exit(84)

def setTasks():
    file = open(sys.argv[1], 'r')
    _tasks = file.read().strip()
    _tasks = _tasks.split('\n')
    Tasks = []
    try:
        for x in range(len(_tasks)):
            tmp = _tasks[x].split(';')
            Tasks.append(TaskClass(tmp[0], tmp[2], tmp[3:]))
    except:
        sys.exit(84)
    return Tasks

def removeTaskFromList(Tasks, Name):
    for x in range(len(Tasks)):
        for y in range(len(Tasks[x].Req)):
            if len(Tasks[x].Req) > 0 and Tasks[x].Req[y] == Name:
                Tasks[x].Req.pop(y)
                break
    for x in range(len(Tasks)):
        if Tasks[x].Name == Name:
            Tasks.pop(x)
            break

def findNextNeed(Tasks, cur):
    minInt = Time
    for task in Tasks:
        if cur.Name in task.Needs:
            minInt = min(minInt, task.Interval[0])
    return minInt

def findMax(Tasks):
    maxV = 0
    for task in Tasks:
        maxV = max(maxV, task.Interval[1])
    return maxV

def setInterval(Tasks):
    for task in Tasks:
        if isNeeded(Tasks, task) == False:
            timer = findMax(Tasks)
            task.Interval = (task.Interval[0], task.Interval[1], timer - task.Interval[1])
        else:
            timer = 0
            timer = findNextNeed(Tasks, task)
            if timer != task.Interval[1]:
                task.Interval = (task.Interval[0], task.Interval[1], timer - task.Interval[1])

def isRequired(Tasks, cur):
    for task in Tasks:
        if cur.Name in task.Req:
            return True
    return False

def isNeeded(Tasks, cur):
    for task in Tasks:
        if cur.Name in task.Needs:
            return True
    return False

def getMaxTime(Tasks, removed):
    maxT = 0
    for task in removed:
        if isRequired(Tasks, task):
            maxT = max(maxT, task.Turns)
    return maxT

def execTasks(Tasks, executedTasks):
    global Time
    tmpTasks = []
    toBeRemoved = []
    for task in Tasks:
        if task.Req == []:
            task.Interval = (Time, Time + task.Turns, 0)
            tmpTasks.append(task)
            toBeRemoved.append(task)
            executedTasks.append(task)
    Time += getMaxTime(Tasks, toBeRemoved)
    for task in toBeRemoved:
        removeTaskFromList(Tasks, task.Name)
    if Tasks:
        execTasks(Tasks, executedTasks)

def execFirstTask(Tasks, executedTasks):
    global Time
    for task in Tasks:
        if task.Req == []:
            task.Interval = (Time, Time + task.Turns, 0)
            Time += task.Turns
            executedTasks.append(task)
            removeTaskFromList(Tasks, task.Name)
    execTasks(Tasks, executedTasks)
    setInterval(executedTasks)

def printGantt(Tasks):
    print()
    for task in Tasks:
        print(task.Name, '\t(', task.Interval[2], ')\t', sep="", end="")
        for x in range(task.Interval[0]):
            print(' ', end="")
        for x in range(task.Turns):
            print('=', end="")
        print()

def printGraph(Tasks):
    time = findMax(Tasks)
    if time > 1:
        print("Total duration of construction:", time, "weeks\n")
    else:
        print("Total duration of construction:", time, "week\n")
    Tasks.sort(key=operator.attrgetter('Interval'))
    for task in Tasks:
        if task.Interval[2] != 0:
            print(task.Name, " must begin between t=", task.Interval[0], " and t=", task.Interval[0] + task.Interval[2], sep="")
        else:
            print(task.Name, " must begin at t=", task.Interval[0], sep="")
    printGantt(Tasks)
    
def main():
    checkParams()
    Tasks = setTasks()
    executedTasks = []
    execFirstTask(Tasks, executedTasks)
    printGraph(executedTasks)


if __name__ == "__main__":
	main()