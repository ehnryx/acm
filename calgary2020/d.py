from sys import stdin, stdout

n, m = [int(x) for x in stdin.readline().split()]
need = [int(x) for x in stdin.readline().split()]
dist = [[None for i in range(n)] for j in range(n)]
deg = [0 for i in range(n)]
for i in range(m):
    a, b, c = [int(x) for x in stdin.readline().split()]
    dist[a][b] = c
    deg[a] += 1

done = [False for i in range(n)]
for bs in range(n):
    for i in range(n):
        if deg[i] == 0 and not done[i]:
            done[i] = True
            for j in range(n):
                if dist[j][i] is not None:
                    need[j] += need[i] * dist[j][i];
                    deg[j] -= 1

stdout.write(' '.join([str(x) for x in need]) + '\n')
