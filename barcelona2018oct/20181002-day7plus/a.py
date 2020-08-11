from sys import stdin, stdout
from collections import deque

n, m = map(int, stdin.readline().split())

grid = []
grid.append(['#' for i in range(m+2)])
for i in range(n):
  grid.append('#' + stdin.readline() + '#')
grid.append(['#' for i in range(m+2)])
n += 2
m += 2

horz = [[0 for i in range(m)] for j in range(n)]
vert = [[0 for i in range(m)] for j in range(n)]
k = 0
for i in range(1, n):
  for j in range(1, m):
    if grid[i][j] == '.':
      horz[i][j] = horz[i][j-1] + 1
      k = max(k, horz[i][j])
for j in range(1, m):
  for i in range(1, n):
    if grid[i][j] == '.':
      vert[i][j] = vert[i-1][j] + 1
      k = max(k, vert[i][j])

dx = [0,0,1,-1]
dy = [1,-1,0,0]

ans = 0
vis = [[0 for i in range(m)] for j in range(n)]
for i in range(1, n-1):
  for j in range(1, m-1):
    if grid[i][j] == '.' and not vis[i][j]:
      cnt = cnth = cntv = 0
      todo = deque()
      vis[i][j] = 1
      todo.append((i,j))
      while todo:
        a, b = todo.pop()
        cnt += 1
        if horz[a][b] == k:
          cnth += 1
        if vert[a][b] == k:
          cntv += 1
        for z in range(4):
          na = a + dx[z]
          nb = b + dy[z]
          if grid[na][nb] == '.' and not vis[na][nb]:
            vis[na][nb] = 1
            todo.append((na,nb))
      res = 0
      if cnt == cnth*k:
        res += 1
      if cnt == cntv*k:
        res += 1
      if res == 0:
        print(0)
        break
      elif res == 2:
        ans += 1
  else:
    continue
  break
else:
  print(2**ans)

