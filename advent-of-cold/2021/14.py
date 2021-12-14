from collections import deque, defaultdict
from itertools import product, permutations, accumulate
from itertools import zip_longest, groupby, takewhile
import sys
big = 1999999999999999999
IN = [ x.strip() for x in sys.stdin ]

s = IN[0]
t = {}
for r in IN[2:]:
  a, b = r.split(' -> ')
  t[a] = b

t[s[-1] + '0'] = '0'
t['00'] = '0'

cnt = defaultdict(int)
for j in range(1, len(s)):
  cnt[s[j-1:j+1]] += 1
cnt[s[-1] + '0'] = 1

for i in range(40):
  nxt = defaultdict(int)
  for c in cnt:
    nxt[c[0] + t[c]] += cnt[c]
    nxt[t[c] + c[1]] += cnt[c]
  cnt = nxt

A = defaultdict(int)
for k,v in cnt.items():
  if k[0] != '0':
    A[k[0]] += v

v = sorted(list(A.values()))
print(v[-1] - v[0])

