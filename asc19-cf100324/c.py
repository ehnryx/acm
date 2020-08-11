from fractions import Fraction

infile = open("casino.in", "r")
outfile = open("casino.out", "w")

n, m, k, c, l = [int(x) for x in infile.readline().strip().split()]
wheel = [[0 for i in range(26)] for j in range(n)]
for i in range(n):
  for v in infile.readline().strip():
    wheel[i][ord(v)-ord('A')] += 1

ans = 0
for i in range(c):
  s, pay = infile.readline().strip().split()
  pay = int(pay)
  cnt = 1
  for i in range(n):
    if s[i] == '*':
      cnt *= m
    else:
      cnt *= wheel[i][ord(s[i])-ord('A')]
  ans += Fraction(pay * cnt, m ** n)

if ans > 1:
  ans -= 1
  outfile.write("{}/{}\n".format(ans.numerator, ans.denominator))
  outfile.write("{}\n".format(l))
  outfile.write("{}\n".format(" ".join([str(x+1) for x in range(l)])))
else:
  outfile.write("0/1\n")
  outfile.write("0\n")


