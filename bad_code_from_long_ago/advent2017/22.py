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

lim = 1000

grid = []
for i in range(0, lim):
  grid.append(['.' for x in range(0, 25+2*lim)])
for line in stdin:
  grid.append(['.' for x in range(0, lim)] + [x for x in line.strip()] + ['.' for x in range(0, lim)])
for i in range(0, lim):
  grid.append(['.' for x in range(0, 25+2*lim)])

dx = -1 + 0j
x = (lim+12) + (lim+12)*1j

ans = 0
i = 0
while i < 10000000:
  i += 1
  a = int(x.real)
  b = int(x.imag)
  if grid[a][b] == '.':
    dx *= 1j
    grid[a][b] = 'W'
  elif grid[a][b] == 'W':
    grid[a][b] = '#'
    ans += 1
  elif grid[a][b] == 'F':
    dx *= -1
    grid[a][b] = '.'
  else:
    dx *= -1j
    grid[a][b] = 'F'
  x += dx

print ans

