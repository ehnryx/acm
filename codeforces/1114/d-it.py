from sys import stdin, stdout, stderr, setrecursionlimit
setrecursionlimit(0x3f3f3f3f)

n = int(stdin.readline())
a = [ int(x) for x in stdin.readline().split() ]

dp = [ [ None for i in range(n) ] for j in range(n) ]

for i in range(n):
  dp[i][i] = 0

for d in range(1,n):
  for i in range(n-d):
    if a[i] == a[i+1]:
      dp[i][i+d] = dp[i+1][i+d]
    elif a[i+d] == a[i+d-1]:
      dp[i][i+d] = dp[i][i+d-1]
    elif a[i] == a[i+d]:
      dp[i][i+d] = 1 + dp[i+1][i+d-1]
    else:
      dp[i][i+d] = 1 + min(dp[i+1][i+d], dp[i][i+d-1])

stdout.write('{}\n'.format(dp[0][n-1]))
