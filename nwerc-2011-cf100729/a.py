from sys import stdin, stdout, stderr
from math import factorial

K = 27 # pray

def calc(n, k):
    r = 1
    for i in range(k):
        r *= n-i
    return r

T = int(stdin.readline())
for tt in range(T):
    m = int(stdin.readline())
    ans = []
    seen = set()
    for k in range(1, K):
        v = m * factorial(k)
        l = k
        r = m*k
        while l <= r:
            n = (l+r)//2
            cur = calc(n, k)
            if cur == v:
                ans.append((n,k))
                seen.add((n,k))
                break
            elif cur < v:
                l = n+1
            else:
                r = n-1
    n = len(ans)
    for i in range(n):
        if (ans[i][0], ans[i][0]-ans[i][1]) not in seen:
            ans.append((ans[i][0], ans[i][0]-ans[i][1]))
    ans.sort()
    stdout.write("{}\n".format(len(ans)))
    stdout.write(" ".join(["({},{})".format(x[0],x[1]) for x in ans]) + "\n")

