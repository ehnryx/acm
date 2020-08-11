from sys import stdin, stdout
from collections import defaultdict, deque

def main():
    n = int(stdin.readline())
    s = stdin.readline()
    d = defaultdict(int)
    cur = (0,0)
    for c in s:
        if c == 'E':
            d[cur] = 1
            cur = (cur[0], cur[1]+1)
        else:
            d[cur] = 2
            cur = (cur[0]+1, cur[1])
    pre = [[None for i in range(n)] for j in range(n)]
    bfs = deque()
    bfs.append((0,0))
    pre[0][0] = (-1,-1)
    while bfs:
        cur = bfs.popleft()
        if cur == (n-1,n-1):
            break
        if d[cur] != 1:
            x = cur[0]
            y = cur[1]+1
            if x < n and y < n and pre[x][y] is None:
                pre[x][y] = cur
                bfs.append((x,y))
        if d[cur] != 2:
            x = cur[0]+1
            y = cur[1]
            if x < n and y < n and pre[x][y] is None:
                pre[x][y] = cur
                bfs.append((x,y))
    ans = []
    t = (n-1,n-1)
    while pre[t[0]][t[1]] != (-1,-1):
        p = pre[t[0]][t[1]]
        if t[0] == p[0]:
            ans.append('E')
        else:
            ans.append('S')
        t = p
    stdout.write(''.join(ans[::-1]))
    stdout.write('\n')

T = int(stdin.readline())
for tt in range(1,T+1):
    stdout.write('Case #{}: '.format(tt))
    main()
