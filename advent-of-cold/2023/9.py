def extra(L):
  Ls = [L]
  while min(L) != max(L):
    Ln = []
    for i in range(1, len(L)):
      Ln.append(L[i] - L[i-1])
    L = Ln
    Ls.append(L)
  for i in range(len(Ls)-1, 0, -1):
    Ls[i-1].append(Ls[i-1][-1] + Ls[i][-1])
  return Ls[0][-1]

import sys
I = [L.strip() for L in sys.stdin]
ans = 0
for L in I:
  L = [int(x) for x in L.split()]
  ans += extra(list(reversed(L)))
print(ans)
