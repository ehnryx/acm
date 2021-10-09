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

def dist(a,b,c):
  if a < 0:
    a = -a
    b = -b
    c = -c
  if c < 0:
    d = min(a,-c)
    a -= d
    b += d
    c += d
  if b > 0 and c > 0:
    d = min(b,c)
    a += d
    b -= d
    c -= d
  if b < 0:
    d = min(a,-b)
    a -= d
    b += d
    c += d
  
  return a+b+c

ans = 0
line = raw_input().split(',')
a = b = c = 0
for i in line:
  if i == "n":
    a += 1
  if i == "nw":
    b += 1
  if i == "ne":
    c += 1
  if i == "s":
    a -= 1
  if i == "se":
    b -= 1
  if i == "sw":
    c -= 1
  ans = max(ans, dist(a,b,c))

print ans
