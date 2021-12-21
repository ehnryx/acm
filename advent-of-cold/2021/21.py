from collections import deque, defaultdict
from itertools import product, permutations, accumulate
from itertools import zip_longest, groupby, takewhile
from heapq import heappush, heappop, heapify, merge
import sys
big = 1999999999999999999
IN = [ x.strip() for x in sys.stdin ]


a, b = [int(x) for x in IN]


A,B=0,0
cnt=0
for i in range(999999):
  cnt+=1

  x=(3*i)%100+1
  y=(3*i+1)%100+1
  z=(3*i+2)%100+1

  #print(x,y,z)

  if i % 2 == 0:
    a = ((a-1)+x+y+z)%10+1
    A+=a
  else:
    b = ((b-1)+x+y+z)%10+1
    B+=b

  if max(A,B)>=1000:
    break

print(A,B,cnt*3)
print(min(A,B)*cnt*3)



