from collections import deque, defaultdict
from itertools import product, permutations, accumulate
from itertools import zip_longest, groupby, takewhile
import sys
big = 1999999999999999999
IN = [ x.strip() for x in sys.stdin ]

adj = defaultdict(list)
for r in IN:
  a, b = r.split('-')
  adj[a].append(b)
  adj[b].append(a)

ans = 0
two = None

def solve(u, vis):
  global ans, two
  if u == "end":
    ans += 1
    return
  if u.lower() == u:
    if u in vis:
      two = u
    else:
      vis.add(u)
  for v in adj[u]:
    if v in vis and (two is not None or v == "start"):
      continue
    solve(v, vis)
  if u.lower() == u:
    if two == u:
      two = None
    else:
      vis.remove(u)

solve("start", set())

print(ans)



