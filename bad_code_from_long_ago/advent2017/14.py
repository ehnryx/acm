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

def hash(rawline):
  line = []
  for i in range(0, len(rawline)):
    line.append(ord(rawline[i]))
  line.append(17)
  line.append(31)
  line.append(73)
  line.append(47)
  line.append(23)

  a = []
  for i in range(0, 256):
    a.append(i)
  pos = 0
  skip = 0
  for ii in range(0, 64):
    for length in line:
      rev = []
      for i in range(0, length):
        rev.append(a[(pos+i)%256])
      for i in range(0, length):
        a[(pos+i)%256] = rev[len(rev)-1-i]
      pos += skip + length
      skip += 1
      
  b = ""
  for i in range(0, 256/16):
    temp = 0
    for j in range(0, 16):
      temp ^= a[16*i+j]
    b += format(temp, "08b")
  return b

root = [-1] * 128*128

def find(i):
  global root
  if root[i] == -1:
    return i
  else:
    root[i] = find(root[i])
    return root[i]

def link(i, j):
  global root
  i = find(i)
  j = find(j)
  if i != j:
    root[j] = i
    return 1
  return 0

merge = 0
ans = 0
line = raw_input()
grid = []
for i in range(0, 128):
  grid.append(hash(line + "-" + str(i)))
  for j in range(0, 128):
    bit = grid[i][j]
    if bit == '1':
      ans += 1
      if i > 0 and grid[i-1][j] == '1':
        merge += link(i*128+j, (i-1)*128+j)
      if j > 0 and grid[i][j-1] == '1':
        merge += link(i*128+j, i*128+j-1)
      if j < 127 and grid[i][j+1] == '1':
        merge += link(i*128+j, i*128+j+1)

print ans - merge


