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

a = []
for i in range(0, 16):
  a.append(chr(i+ord('a')))
init = a

dance = []
for move in raw_input().split(','):
  dance.append(move)

mod = -1
memo = []
i = 0
while i < 0x3f3f3f3f:
  i += 1
  memo.append(a[0:])
  for move in dance:
    if move[0] == 's':
      x = int(move[1:])
      a = a[-x:] + a[:-x]
    elif move[0] == 'x':
      x,y = map(int, move[1:].split('/'))
      a[x], a[y] = a[y], a[x]
    else:
      x,y = move[1:].split('/')
      x,y = a.index(x), a.index(y)
      a[x], a[y] = a[y], a[x]
  try:
    mod = i - memo.index(a)
    break
  except:
    pass

print "".join(memo[10**9%mod])

