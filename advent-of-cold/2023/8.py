def gcd(a, b):
  if not b: return a
  return gcd(b, a % b)

import sys
I = [L.strip() for L in sys.stdin if L.strip()]
ss = I[0]
g = {}
for L in I[1:]:
  u, _, l, r = L.split()
  l = l[1:-1]
  r = r[:-1]
  g[u] = (l, r)

cyc = {}
for u in g:
  if u[-1] != "Z": continue
  o = u
  i = 0
  while u[-1] != "Z" or i == 0:
    s = ss[i % len(ss)]
    u = g[u][s == "R"]
    i += 1
  assert o == u
  cyc[u] = i

ans = 1
for u in g:
  if u[-1] != "A": continue
  i = 0
  while u[-1] != "Z":
    s = ss[i % len(ss)]
    u = g[u][s == "R"]
    i += 1
  # i mod cyc[u]
  print(f"{i} mod {cyc[u]}")
  ans = ans * cyc[u] // gcd(ans, cyc[u])
print(ans)
