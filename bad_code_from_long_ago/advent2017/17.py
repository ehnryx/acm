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

a = [0]

diff = int(raw_input())

i = 0
pos = 0
ans = 0
lim = 50*10**6
while i < lim:
  i += 1
  pos = (pos+diff)%i
  if pos == 0:
    ans = i
  pos += 1

print ans


