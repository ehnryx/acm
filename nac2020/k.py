from sys import stdin, stdout

L = 18
n, m = [int(x) for x in stdin.readline().split()]

adj = [[] for i in range(n+1)]
sz = [0 for i in range(n+1)]
dep = [0 for i in range(n+1)]
anc = [[0 for j in range(L)] for i in range(n+1)]

def lca(a, b):
    if dep[a] < dep[b]:
        a, b = b, a
    for j in range(L-1, -1, -1):
        if dep[anc[a][j]] >= dep[b]:
            a = anc[a][j]
    if a == b:
        return a
    for j in range(L-1, -1, -1):
        if anc[a][j] != anc[b][j]:
            a = anc[a][j]
            b = anc[b][j]
    return anc[a][0]

for i in range(1, n):
    a, b = [int(x) for x in stdin.readline().split()]
    adj[a].append(b)
    adj[b].append(a)

order = []
dfs = []
dfs.append((1, 0))
while dfs:
    u, p = dfs.pop()
    order.append((u, p))
    dep[u] = dep[p] + 1
    anc[u][0] = p
    for j in range(1, L):
        anc[u][j] = anc[anc[u][j-1]][j-1]
    for v in adj[u]:
        if v != p:
            dfs.append((v, u))

for u, p in reversed(order):
    sz[u] = 1
    for v in adj[u]:
        if v != p:
            sz[u] += sz[v]

for i in range(m):
    a, b = [int(x) for x in stdin.readline().split()]
    c = lca(a, b)
    k = dep[a] + dep[b] - 2*dep[c]
    res = n - k - 1 + (k+1)*(k+2)//2
    stdout.write('{}\n'.format(res))

