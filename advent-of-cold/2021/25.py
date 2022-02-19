from collections import deque, defaultdict
from itertools import product, permutations, accumulate
from itertools import zip_longest, groupby, takewhile
from heapq import heappush, heappop, heapify, merge
import sys
big = 1999999999999999999
IN = [ x.strip() for x in sys.stdin ]

g = [list(r) for r in IN]
n=len(g)
m=len(g[0])

print(n,m)

ans=0

while True:
  mv = 0

  ok = [[False for i in range(m)]for j in range(n)]
  for i in range(n):
    for j in range(m):
      nj = (j+1)%m
      if g[i][j]=='>' and g[i][nj] == '.':
        ok[i][j] = True
  for i in range(n):
    for j in range(m):
      nj = (j+1)%m
      if ok[i][j]:
        g[i][j],g[i][nj]=g[i][nj],g[i][j]
        mv+=1

  ok = [[False for i in range(m)]for j in range(n)]
  for j in range(m):
    for i in range(n):
      ni = (i+1)%n
      if g[i][j] == 'v' and g[ni][j] == '.':
        ok[i][j] = True
  for j in range(m):
    for i in range(n):
      ni = (i+1)%n
      if ok[i][j]:
        g[i][j],g[ni][j]=g[ni][j],g[i][j]
        mv+=1

  ans += 1
  #print('\n'.join([''.join(r) for r in g]))
  #print("")
  #break
  if mv == 0:
    break

print(ans)

