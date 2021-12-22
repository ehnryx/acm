from collections import deque, defaultdict
from itertools import product, permutations, accumulate
from itertools import zip_longest, groupby, takewhile
from heapq import heappush, heappop, heapify, merge
import sys
big = 1999999999999999999
IN = [ x.strip() for x in sys.stdin ]

M = 50
MM = 2*M + 1

g = [[[0] * MM for i in range(MM)] for j in range(MM)]


for R in IN:
  r = R.split()
  x1,x2,y1,y2,z1,z2=[int(x) for x in r[1:]]
  if r[0] == 'on':
    v = 1
  else:
    v = 0

  x1=max(x1,-50)
  y1=max(y1,-50)
  z1=max(z1,-50)
  x2=min(x2, 50)
  y2=min(y2, 50)
  z2=min(z2, 50)

  for i in range(x1,x2+1):
    for j in range(y1,y2+1):
      for k in range(z1,z2+1):
        g[i][j][k] = v


ans=0
for S in g:
  for P in S:
    for x in P:
      ans += x

print(ans)



