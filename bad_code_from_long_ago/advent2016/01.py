from math import *
from sets import *
from collections import *
from sys import *
from os import *
from re import *

def main():

  seen = set([0j])

  s = raw_input()
  a = s.split(", ")
  d = 1j
  p = 0j
  for it in a:
    if (it[0] == 'R'): d *= -1j
    else: d *= 1j
    for j in range(0, int(it[1:])):
      p += d
      if p in seen:
        print p
        return
      seen.add(p)
  print abs(p.real) + abs(p.imag)

if __name__ == "__main__":
  main()
