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

a = int(raw_input().split()[-1])
b = int(raw_input().split()[-1])

aa = 16807
bb = 48271
div = 2147483647
mod = 2**16

ans = 0
lim = 5*10**6
for i in range(0, lim):
  a *= aa
  a %= div
  while a % 4 != 0:
    a *= aa
    a %= div
  b *= bb
  b %= div
  while b % 8 != 0:
    b *= bb
    b %= div
  if a % mod == b % mod:
    ans += 1

print ans

