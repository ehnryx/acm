import sys
g = [L.strip() for L in sys.stdin]
good = [[[] for _ in L] for L in g]
for i in range(len(g)):
  for j in range(len(g[i])):
    if not g[i][j].isdigit(): continue
    for di, dj in [(1, 1), (1, 0), (1, -1),
                   (0, 1), (0, 0), (0, -1),
                   (-1, 1), (-1, 0), (-1, -1),]:
      if i+di < 0 or i+di >= len(g): continue
      if j+dj < 0 or j+dj >= len(g[i]): continue
      #if g[i+di][j+dj] != '.' and not g[i+di][j+dj].isdigit():
      if g[i+di][j+dj] == "*":
        good[i][j].append((i+di, j+dj))

vals = [[[] for _ in L] for L in g]
ans = 0
for i in range(len(g)):
  j = 0
  while j < len(g[i]):
    if not g[i][j].isdigit():
      j += 1
      continue
    res = []
    start = j
    while j < len(g[i]) and g[i][j].isdigit():
      res += good[i][j]
      j += 1
    v = int(g[i][start:j])
    for x, y in set(res):
      vals[x][y].append(v)

for r in vals:
  for c in r:
    if len(c) == 2:
      ans += c[0] * c[1]

print(ans)
