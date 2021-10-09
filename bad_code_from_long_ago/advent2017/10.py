#!/usr/env
from math import *
from sets import *
from collections import *
from sys import *
from re import *
from os import *

# advent of code
from hashlib import *
#

rawline = raw_input()
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
    
# b = []
b = ""
for i in range(0, 256/16):
  temp = 0
  for j in range(0, 16):
    temp ^= a[16*i+j]
  # b.append(hex(temp)[2:])
  b += format(temp, "02x")

# print ''.join(b)
print b
