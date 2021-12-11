from collections import deque, defaultdict
import sys
IN = [ x.strip() for x in sys.stdin ]

g = [[int(x) for x in r] for r in IN]

for it in range(100000):
    ans=0
    stk = []
    for i in range(len(g)):
        for j in range(len(g[0])):
            g[i][j] += 1
            if g[i][j] > 9:
                stk.append((i,j))
    while stk:
        i,j = stk[-1]
        stk.pop()
        for di in [-1,0,1]:
            for dj in [-1,0,1]:
                ni,nj = i+di,j+dj
                if ni in range(len(g)) and nj in range(len(g[0])) and g[ni][nj] <= 9:
                    g[ni][nj] += 1
                    if g[ni][nj] > 9:
                        stk.append((ni,nj))
        ans+=1
    for i in range(len(g)):
        for j in range(len(g[0])):
            if g[i][j] > 9:
                g[i][j] = 0
    print(g)
    if ans == len(g)*len(g[0]):
        print(it+1)
        break
#print(ans)

