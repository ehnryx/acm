from collections import deque, defaultdict
from itertools import product, permutations, accumulate
from itertools import zip_longest, groupby, takewhile
from heapq import heappush, heappop, heapify, merge
import sys
big = 1999999999999999999
IN = [ x.strip() for x in sys.stdin ]

ans = ""
for c in IN[0]:
  if ord(c) <= ord('9'):
    s = str(bin(int(c)))[2:]
    while len(s) < 4:
      s = '0' + s
    ans += s
  else:
    s = str(bin(ord(c)-ord('A')+10))[2:]
    while len(s) < 4:
      s = '0' + s
    ans += s
  assert len(s) == 4

print(ans)

#out = 0

i = 0

stk = []
have = []

def solve():
  global i
  version = int(ans[i:i+3], 2)
  i += 3
  for I in range(len(have)):
    have[I] += 3
  t = int(ans[i:i+3], 2)
  i += 3
  for I in range(len(have)):
    have[I] += 3
  #out += version
  F = 0
  if t == 4:
    print("value")
    while ans[i:i+5][0] != '0':
      F = F*16 + int(ans[i+1:i+5], 2)
      i += 5
      for I in range(len(have)):
        have[I] += 5
    F = F*16 + int(ans[i+1:i+5], 2)
    i += 5
    for I in range(len(have)):
      have[I] += 5

    print("F=",F)
    return F
  else:
    print("EHROSI")
    Lt = int(ans[i:i+1], 2)
    i += 1
    for I in range(len(have)):
      have[I] += 1
    if Lt == 0:
      L = int(ans[i:i+15], 2)
      i += 15
      for I in range(len(have)):
        have[I] += 15
    else:
      L = int(ans[i:i+11], 2)
      i += 11
      for I in range(len(have)):
        have[I] += 11
    F = []
    print("L=",L)
    stk.append(L)
    have.append(0)

    if Lt == 0:
      while have[-1] + 6 < stk[-1]:
        F.append(solve())
      while have[-1] < stk[-1]:
        i += 1
        for I in range(len(have)):
          have[I] += 1
    else:
      for j in range(L):
        F.append(solve())

    stk.pop()
    have.pop()

    print(F)

    if t == 0:
      return sum(F)
    if t == 1:
      P = 1
      for c in F:
        P *= c
      return P
    if t == 2:
      return min(F)
    if t == 3:
      return max(F)
    if t == 5:
      return int(F[0] > F[1])
    if t == 6:
      return int(F[0] < F[1])
    if t == 7:
      return int(F[0] == F[1])

stk.append(big)
have.append(0)
O =solve()

print(len(have), have[-1], len(ans))

print(O)


"""
i = 0
while i + 6 < len(ans):
  version = int(ans[i:i+3], 2)
  i += 3
  t = int(ans[i:i+3], 2)
  i += 3
  out += version
  if t == 4:
    while ans[i:i+5][0] != '0':
      i += 5
    i += 5
  else:
    Lt = int(ans[i:i+1], 2)
    i += 1
    if Lt == 0:
      L = int(ans[i:i+15], 2)
      i += 15
    else:
      L = int(ans[i:i+11], 2)
      i += 11
    # ignore
"""

#print(out)
