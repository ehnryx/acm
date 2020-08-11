from sys import stdin, stdout, stderr
from collections import deque

n,m = map(int,stdin.readline().split())
ai = [int(x) for x in stdin.readline().split()]
bi = [int(x) for x in stdin.readline().split()]

N = 2*n+2
M = 4*m + 6*n
cap = [None for i in range(M)]
flow = [0 for i in range(M)]
adj = [[] for i in range(N)]

s = 0
t = 2*n+1

INF = 0x3f3f3f3f

eid = 0
def add_edge(a,b,c):
  global eid, adj, cap
  adj[a].append((b,eid))
  cap[eid] = c
  eid += 1

for i in range(m):
  a,b = map(int,stdin.readline().split())
  add_edge(a,n+b,INF)
  add_edge(n+b,a,0)
  add_edge(b,n+a,INF)
  add_edge(n+a,b,0)
for i in range(n):
  add_edge(s,i+1,ai[i])
  add_edge(i+1,s,0)
  add_edge(n+i+1,t,bi[i])
  add_edge(t,n+i+1,0)
  add_edge(i+1,n+i+1,INF)
  add_edge(n+i+1,i+1,0)

ans = 0
while True:
  par = [None for i in range(N)]
  minf = [INF for i in range(N)]
  bfs = deque()
  bfs.append(s)
  par[s] = (-1,-1)
  while bfs:
    u = bfs.pop()
    if u == t:
      break
    for v,e in adj[u]:
      if par[v] is None and flow[e] < cap[e]:
        bfs.append(v)
        par[v] = (u,e)
        minf[v] = min(minf[u], cap[e] - flow[e])
  v = t
  if par[t] is None: break
  while par[v][0] != -1:
    u,e = par[v]
    flow[e] += minf[t]
    flow[e^1] -= minf[t]
    v = u
  ans += minf[t]

if ans != sum(ai) or ans != sum(bi):
  stdout.write('NO\n')
else:
  stdout.write('YES\n')
  grid = [[0 for j in range(n)] for i in range(n)]
  for u in range(1,n+1):
    for v,e in adj[u]:
      if flow[e] > 0 and 1 <= v-n and v-n <= n:
        grid[u-1][v-n-1] += flow[e]
  stdout.write('\n'.join([' '.join([str(x) for x in line]) for line in grid]) + '\n')
