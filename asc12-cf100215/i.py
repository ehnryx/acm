infile = open("regular.in", "r")
outfile = open("regular.out", "w")

n = int(infile.readline())

dp = [[[0 for i in range(n+1)] for j in range(n+1)] for k in range(n+1)]
dp[0][0][0] = 1
for i in range(n+1):
  for j in range(i+1):
    for k in range(j+1):
      if i:
        dp[i][j][k] += dp[i-1][j][k]
      if j:
        dp[i][j][k] += dp[i][j-1][k]
      if k:
        dp[i][j][k] += dp[i][j][k-1]

outfile.write("{}\n".format(dp[n][n][n]))
