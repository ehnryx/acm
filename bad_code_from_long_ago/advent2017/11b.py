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

line = raw_input().split(',')
ans = 0
a = b = c = 0
for i in line:
  if i == "n":
    a += 1
    b -= 1
  if i == "s":
    a -= 1
    b += 1
  if i == "ne":
    a += 1
    c -= 1
  if i == "sw":
    a -= 1
    c += 1
  if i == "se":
    b += 1
    c -= 1
  if i == "nw":
    b -= 1
    c += 1
  ans = max(ans, abs(a), abs(b), abs(c))
print ans




