from collections import deque, defaultdict
from itertools import product, permutations, accumulate
from itertools import zip_longest, groupby, takewhile
from heapq import heappush, heappop, heapify, merge
import sys
big = 1999999999999999999
IN = [ x.strip() for x in sys.stdin ]

A = IN[0]
IN = IN[2:]

n = len(IN)
m = len(IN[0])

M = 150
g = [['.' for i in range(m + 2*M)] for j in range(n + 2*M)]

for i in range(n):
  g[i+M][M:M+m] = IN[i]

#print(g)


for t in range(50):
  ng = [['.' for i in range(m + 2*M)] for j in range(n + 2*M)]
  for i in range(1, n+2*M - 1):
    for j in range(1, m+2*M - 1):
      #ii = i + M - t
      #jj = j + M - t
      ii = i
      jj = j
      R = g[ii-1][jj-1:jj+2] + g[ii][jj-1:jj+2] + g[ii+1][jj-1:jj+2]
      s = ''.join(R)
      s = s.replace('.','0')
      s = s.replace('#','1')
      v = int(s,2)
      ng[ii][jj] = A[v]
  g = ng



print('\n'.join([''.join([x for x in r]) for r in ng]))

ans = 0
for i in range(99, n+2*M - 99):
  for j in range(99, m+2*M - 99):
    if g[i][j] == '#':
      ans += 1
print(ans)

