from collections import deque, defaultdict
from itertools import product, permutations, accumulate
from itertools import zip_longest, groupby, takewhile
import sys
big = 1999999999999999999
IN = [ x.strip() for x in sys.stdin ]

s = set()
for line in IN:
  if line[:4] == "fold":
    c, v = line.split()[-1].split('=')
    v = int(v)
    if c == 'x':
      ns = set()
      for x,y in s:
        if x >= v:
          x = v - (x-v)
        ns.add((x,y))
    else:
      ns = set()
      for x,y in s:
        if y >= v:
          y = v - (y-v)
        ns.add((x,y))
    s = ns
    #break # WTF
  else:
    a, b = [int(x) for x in line.split(',')]
    s.add((a,b))

print(len(s))

g = [[' ']*100 for i in range(100)]
for x,y in s:
  g[x][y] = '#'
for r in g:
  print(''.join(r))
y
