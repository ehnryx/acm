from fractions import Fraction

n = int(input())
a = [int(x) for x in input().split()]

ans = Fraction(a[-1])
for x in reversed(a[:-1]):
  ans = x + 1 / ans

print("{}/{}".format(ans.numerator, ans.denominator))

