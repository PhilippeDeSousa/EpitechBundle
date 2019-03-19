#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
import os
from enum import Enum

class CaseType(Enum):
    Empty = -1
    Pacman = -2
    Wall = -3
    Ghost = -4

class PacClass:
    def __init__(self, _map, _wall, _space):
        self.Map = _map
        self.Wall = _wall
        self.Space = _space
        self.Tail = list(tuple())
        self.lenX = int
        self.lenY = int

def displayMap(Pacman):
    for y in range(Pacman.lenY):
        for x in range(Pacman.lenX):
            if Pacman.Map[y][x] == CaseType.Empty.value:
                print(Pacman.Space, end="")
            elif Pacman.Map[y][x] == CaseType.Wall.value:
                print(Pacman.Wall, end="")
            elif Pacman.Map[y][x] == CaseType.Pacman.value:
                print('P', end="")
            elif Pacman.Map[y][x] == CaseType.Ghost.value:
                print('F', end="")
            else:
                print(Pacman.Map[y][x], end="")
        print()

def checkParams():
    if len(sys.argv) != 4:
        print("Error: 4 arguments required")
        sys.exit(84)
    elif len(sys.argv[2]) > 1 or len(sys.argv[3]) > 1:
        print("Error: invalid char")
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

def checkMap(_map):
    sizeY = len(_map); sizeX = len(_map[0])
    pac = 0; gh = 0;
    for y in range(sizeY):
        for x in range(sizeX):
            if _map[y][x] == 'F':
                gh += 1
            elif _map[y][x] == 'P':
                pac += 1
            elif _map[y][x] != 'P' and _map[y][x] != 'F' and _map[y][x] != '0' and _map[y][x] != '1':
                print("Error: Character unothorized in map")
                sys.exit(84)
    if pac == 0 or gh == 0 or pac > 1 or gh > 1:
        print("Error: Map format is wrong")
        sys.exit(84)

def setMap():
    file = open(sys.argv[1], 'r')
    _map = file.read().strip()
    _map = _map.split('\n')
    checkMap(_map)
    sizeY = len(_map); sizeX = len(_map[0])
    intMap = [[CaseType.Empty.value for x in range(sizeX)] for y in range(sizeY)]
    for y in range(sizeY):
        for x in range(sizeX):
            if _map[y][x] == '1':
                intMap[y][x] = CaseType.Wall.value
            elif _map[y][x] == 'F':
                intMap[y][x] = CaseType.Ghost.value
            elif _map[y][x] == 'P':
                intMap[y][x] = CaseType.Pacman.value
            elif _map[y][x] == '0':
                intMap[y][x] = CaseType.Empty.value
    return intMap

def findGhost(Pacman):
    for y in range(Pacman.lenY):
        for x in range(Pacman.lenX):
            if (Pacman.Map[y][x] == CaseType.Ghost.value):
                return x, y
    return 0, 0

def checkPos(Pacman, posy, posx, cycle):
    if Pacman.Map[posy][posx] == CaseType.Ghost.value:
        return
    elif Pacman.Map[posy][posx] == CaseType.Pacman.value:
        displayMap(Pacman)
        sys.exit(0)
    elif Pacman.Map[posy][posx] == CaseType.Empty.value:
        tmp = (posy, posx)
        Pacman.Tail.append(tmp)
        Pacman.Map[posy][posx] = cycle % 10

def checkAround(Pacman, posy, posx, cycle):
    checkPos(Pacman, posy - 1, posx, cycle)
    checkPos(Pacman, posy, posx + 1, cycle)
    checkPos(Pacman, posy + 1, posx, cycle)
    checkPos(Pacman, posy, posx - 1, cycle)

def algoLoop(Pacman, Cycle):
    if Cycle == 0:
        posx, posy = findGhost(Pacman)
        checkAround(Pacman, posy, posx, Cycle + 1)
    else:
        for _ in range(len(Pacman.Tail)):
            checkAround(Pacman, Pacman.Tail[0][0], Pacman.Tail[0][1], Cycle + 1)
            Pacman.Tail.pop(0)
    return Cycle + 1

def main():
    checkParams()
    _map = setMap()
    Pacman = PacClass(_map, sys.argv[2], sys.argv[3])
    Pacman.lenX = len(_map[0]); Pacman.lenY = len(_map)
    Cycle = 0
    while 1:
        Cycle = algoLoop(Pacman, Cycle)
    displayMap(Pacman)

if __name__ == "__main__":
	main()