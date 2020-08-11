from sys import stdin, stdout
from collections import deque

def gcd(a,b):
    while b != 0:
        a,b = b,a%b
    return a

def main():
    n,m = map(int,stdin.readline().split())
    val = [int(x) for x in stdin.readline().split()]
    ans = [None for i in range(m+1)]
    bfs = deque()
    for i in range(1,m):
        if val[i] != val[i-1]:
            bfs.append(i)
    while bfs:
        i = bfs.popleft()
        if val[i] != val[i-1]:
            ans[i] = gcd(val[i], val[i-1])
        else:
            if ans[i+1] is not None:
                ans[i] = val[i]//ans[i+1]
            else:
                ans[i] = val[i]//ans[i-1]
        if i > 1 and ans[i-1] is None:
            bfs.append(i-1)
        if i < m-1 and ans[i+1] is None:
            bfs.append(i+1)
    ans[0] = val[0]//ans[1]
    ans[-1] = val[-1]//ans[-2]

    seen = set()
    for x in ans:
        seen.add(x)
    letter = list(seen)
    letter.sort()
    cur = 'A'
    for x in letter:
        for i in range(m+1):
            if ans[i] == x:
                ans[i] = cur
        cur = chr(ord(cur)+1)
    stdout.write(''.join(ans))
    stdout.write('\n')

T = int(stdin.readline())
for tt in range(1,T+1):
    stdout.write('Case #{}: '.format(tt))
    main()
