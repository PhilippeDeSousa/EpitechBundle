#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
import os
import numpy as np
import math

def checkParams():
    if len(sys.argv) != 8:
        print("Error: 8 arguments required"); sys.exit(84)
    try:
        [float(i) for i in sys.argv[1:]]
    except ValueError:
        print("Error: All arguments must be floats"); sys.exit(84)

def square(nb):
    return nb * nb

def calc_angle(vec):
    print("The incidence angle is:")
    rad = math.acos(vec[2] / (math.sqrt(square(vec[0]) + square(vec[1]) + square(vec[2]))))
    deg = abs(180 * (rad - (math.pi / 2)) / math.pi)
    print(format(deg, '.2f'))

def pong():
    vec_0 = np.array([float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3])])
    vec_1 = np.array([float(sys.argv[4]), float(sys.argv[5]), float(sys.argv[6])])
    n = float(sys.argv[7])

    vec = vec_1 - vec_0

    print("The velocity vector of the ball is:")
    print('(', vec[0], ', ', vec[1], ', ', vec[2], ')', sep='')
    print("At time t + 4, ball coordinates will be:")
    print('(', vec[0] * (n + 1) + vec_0[0], ", ", vec[1] * (n + 1) + vec_0[1], ", ", vec[2] * (n + 1) + vec_0[2], ')', sep="")

    if vec[2] != 0 and -vec_1[2] / vec[2] >= 0 and vec_1[0] != 0:
        calc_angle(vec)
    else:
        print("The ball won’t reach the bat.")

def main():
    checkParams()
    pong()

if __name__ == "__main__":
	main()