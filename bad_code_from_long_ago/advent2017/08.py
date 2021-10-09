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

val = dict()
ans = 0

for line in stdin:
  arr = line.split()

  diff = int(arr[2])
  if arr[1] == "dec":
    diff = -diff

  reg = arr[0]
  if reg not in val:
    val[reg] = 0

  cond = arr[4]
  vc = arr[6]
  cp = arr[5]
  if cond not in val:
    val[cond] = 0
  if cp == '<' and val[cond] < int(vc):
    val[reg] += diff
  if cp == '>' and val[cond] > int(vc):
    val[reg] += diff
  if cp == '<=' and val[cond] <= int(vc):
    val[reg] += diff
  if cp == '>=' and val[cond] >= int(vc):
    val[reg] += diff
  if cp == '==' and val[cond] == int(vc):
    val[reg] += diff
  if cp == '!=' and val[cond] != int(vc):
    val[reg] += diff
  ans = max(ans, val[reg])
print ans

