from sys import stdin, stdout, stderr, setrecursionlimit
setrecursionlimit(0x3f3f3f3f)

n = int(stdin.readline())
a = [ int(x) for x in stdin.readline().split() ]

dp = [ [ None for i in range(n) ] for j in range(n) ]

def solve(l, r):
  if dp[l][r] is not None:
    return dp[l][r]
  if r-l+1 == 1:
    dp[l][r] = 0
  elif a[l] == a[l+1]:
    dp[l][r] = solve(l+1, r)
  elif a[r] == a[r-1]:
    dp[l][r] = solve(l, r-1)
  elif a[l] == a[r]:
    dp[l][r] = 1 + solve(l+1, r-1)
  else:
    dp[l][r] = 1 + min(solve(l+1, r), solve(l, r-1))
  return dp[l][r]

stdout.write('{}\n'.format(solve(0, n-1)))
