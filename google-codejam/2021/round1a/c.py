from sys import stdin, stdout
from fractions import Fraction

N = 120
ncr = [[0 for i in range(N + 1)] for j in range(N + 1)]
for i in range(N + 1):
  ncr[i][0] = 1
  if i > 0:
    ncr[i][i] = 1
    for j in range(1, i):
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1]


def solve1(m):
  a, s = stdin.readline().split()
  s = int(s)

  out = list(a)
  if 2*s < m:
    for i in range(m):
      out[i] = 'T' if out[i] == 'F' else 'F'
    s = m - s

  stdout.write(''.join(out) + " " + str(s) + "/1\n")


def solve2(m):
  a1, s1 = stdin.readline().split()
  a2, s2 = stdin.readline().split()
  s1 = int(s1)
  s2 = int(s2)

  same = []
  different = []
  for i in range(m):
    if a1[i] == a2[i]:
      same.append(i)
    else:
      different.append(i)

  x = (s1 + s2 - len(different)) // 2
  y = s1 - x

  out = list(a1)
  if 2*x < len(same):
    for i in same:
      out[i] = 'T' if out[i] == 'F' else 'F'
    x = len(same) - x
  if 2*y < len(different):
    for i in different:
      out[i] = 'T' if out[i] == 'F' else 'F'
    y = len(different) - y

  stdout.write(''.join(out) + " " + str(x + y) + "/1\n")


def solve3(m):
  a1, s1 = stdin.readline().split()
  a2, s2 = stdin.readline().split()
  a3, s3 = stdin.readline().split()
  s1 = int(s1)
  s2 = int(s2)
  s3 = int(s3)

  same = []
  d1 = []
  d2 = []
  d3 = []
  for i in range(m):
    if a1[i] == a2[i] and a2[i] == a3[i]:
      same.append(i)
    elif a2[i] == a3[i]:
      d1.append(i)
    elif a3[i] == a1[i]:
      d2.append(i)
    elif a1[i] == a2[i]:
      d3.append(i)

  tx, ty, tz, tw = len(same), len(d1), len(d2), len(d3)
  assert(tx + ty + tz + tw == m)

  total = 0
  sumx, sumy, sumz, sumw = 0, 0, 0, 0
  for x in range(tx + 1):
    ys2 = s2 + s3 - 2*x - tz - tw
    zs2 = s1 + s3 - 2*x - ty - tw
    ws2 = s1 + s2 - 2*x - ty - tz
    if ys2 % 2 or zs2 % 2 or ws2 % 2:
      continue
    if ys2 < 0 or zs2 < 0 or ws2 < 0:
      continue

    ys = ys2 // 2
    zs = zs2 // 2
    ws = ws2 // 2
    yd = ty - ys
    zd = tz - zs
    wd = tw - ws
    if yd < 0 or zd < 0 or wd < 0:
      continue

    cnt = ncr[tx][x] * ncr[ty][yd] * ncr[tz][zs] * ncr[tw][ws]
    assert(ncr[ty][yd] == ncr[ty][ys])
    total += cnt
    sumx += x * cnt
    sumy += yd * cnt
    sumz += zs * cnt
    sumw += ws * cnt

  Ex = Fraction(sumx, total)
  Ey = Fraction(sumy, total)
  Ez = Fraction(sumz, total)
  Ew = Fraction(sumw, total)

  out = list(a1)
  if 2 * Ex < tx:
    for i in same:
      out[i] = 'T' if out[i] == 'F' else 'F'
    Ex = tx - Ex
  if 2 * Ey < ty:
    for i in d1:
      out[i] = 'T' if out[i] == 'F' else 'F'
    Ey = ty - Ey
  if 2 * Ez < tz:
    for i in d2:
      out[i] = 'T' if out[i] == 'F' else 'F'
    Ez = tz - Ez
  if 2 * Ew < tw:
    for i in d3:
      out[i] = 'T' if out[i] == 'F' else 'F'
    Ew = tw - Ew

  res = Ex + Ey + Ez + Ew
  stdout.write(''.join(out) + " " + str(res.numerator) + "/" + str(res.denominator) + "\n")


T = int(stdin.readline())
for testnum in range(1, T + 1):
  stdout.write("Case #{}: ".format(testnum))

  n, m = [int(x) for x in stdin.readline().split()]
  if n == 1:
    solve1(m)
  elif n == 2:
    solve2(m)
  else:
    solve3(m)
