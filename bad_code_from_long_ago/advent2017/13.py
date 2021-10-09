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

ran = dict()
for line in stdin:
  ll = map(int, line.split(": "))
  ran[ll[0]] = 2*(ll[1]-1)

ans = 0
while True:
  ans += 1
  shit = False
  for t in ran:
    if (t + ans) % ran[t] == 0:
      shit = True
      break
  if not shit:
    break
print ans

