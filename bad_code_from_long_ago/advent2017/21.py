#!/usr/env
from math import *
from decimal import *
from sets import *
from collections import *
from sys import *
from re import *
from os import *

# advent of code
from hashlib import *
#

to = dict()

for line in stdin:
	it = line.split()
	grid = []
	if len(it) == 6:
		for i in range(0, 2):
			row = []
			for c in it[i]:
				row.append(c)
			grid.append(row)

		rot = grid
		for i in range(0, 4):
			rot = [list(x) for x in reversed(zip(*rot))]
			to[str(rot)] = it[3:]
		rot = grid
		for i in range(0, 4):
			rot = [list(x) for x in reversed(zip(*rot))]
			to[str(rot)] = it[3:]

	else:
		for i in range(0, 3):
			row = []
			for c in it[i]:
				row.append(c)
			grid.append(row)

		rot = grid
		for i in range(0, 4):
			rot = [list(x) for x in reversed(zip(*rot))]
			to[str(rot)] = it[4:]
		grid = list(reversed(grid))
		rot = grid
		for i in range(0, 4):
			rot = [list(x) for x in reversed(zip(*rot))]
			to[str(rot)] = it[4:]

nl = '\n'

grid = [['.', '#', '.'], ['.', '.', '#'], ['#', '#', '#']]
for T in range(0, 18):
	stderr.write("T: " + str(T) + nl)
	next = []
	if len(grid) % 2 == 0:
		next = [[] for x in range(0, len(grid)/2*3)]
		l = len(grid)
		for i in range(0, l, 2):
			for j in range(0, l, 2):
				temp = []
				for ii in range(i, i+2):
					row = []
					for jj in range(j, j+2):
						row.append(grid[ii][jj])
					temp.append(row)

				r = i/2*3
				for row in to[str(temp)]:
					for c in row:
						next[r].append(c)
					r += 1

	else:
		next = [[] for x in range(0, len(grid)/3*4)]
		l = len(grid)
		for i in range(0, l, 3):
			for j in range(0, l, 3):
				temp = []
				for ii in range(i, i+3):
					row = []
					for jj in range(j, j+3):
						row.append(grid[ii][jj])
					temp.append(row)

				r = i/3*4
				for row in to[str(temp)]:
					for c in row:
						next[r].append(c)
					r += 1
	grid = next

ans = 0
for row in grid:
	for c in row:
		if c == '#':
			ans += 1
print ans



