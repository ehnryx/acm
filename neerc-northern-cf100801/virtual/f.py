from fractions import Fraction
from sys import stdin
import string

fileobj = open('fygon.in')
parts = []
counter = []
for line in fileobj:
    if parts and line == parts[-1]:
        counter[-1] += 1
    else:
        parts.append(line)
        counter.append(1)
for i in range(len(parts)):
    idx = parts[i].find('lag')
    if idx != -1:
        parts[i] = parts[i][:idx] + 'ubccounter += {}\n'.format(counter[i])
code = ''.join(parts)
code = 'ubccounter = 0\nn = locals()["n"]\n'+ code + 'locals()["mapthing"]["ans"] = ubccounter\n'
# print(code)

def evalFor(n):
    mapthing = {}
    exec(code)
    # print("{} {}".format(n, mapthing['ans']))
    return mapthing['ans']

ev = [] # evaluated amounts

a = []
n = -1
ev.append(Fraction(evalFor(6), 1))
for i in range(7, 7+6, 1):
    ev.append(Fraction(evalFor(i), 1))
    g = []
    for x in ev:
        g.append(x)

    sz = len(g)
    while sz > 2:
        for j in range(sz-1):
            g[j] -= g[j+1]
        sz -= 1

    if g[0] == g[1]:
        n = i-6
        break

if n == -1:
    n = 7

#print("n = {}".format(n))

for i in range(1, n+1):
    a.append([])
    v = 1
    for j in range(0, n):
        a[i-1].append(Fraction(v, 1))
        v *= i+5
    a[i-1].append(Fraction(ev[i-1], 1))
    """
    s = ""
    for x in a[i-1]:
        s += '{} '.format(x)
    print(s)
    """

m = n+1

def swaprow(a, i, j):
    for k in range(m):
        tmp = a[i][k]
        a[i][k] = a[j][k]
        a[j][k] = tmp


j = 0
for i in range(n):
    # find column with this
    found = -1
    while found == -1 and j < m:
        for k in range(i, n):
            if a[k][j] != 0:
                found = k
                break
        j += 1
    j -= 1

    if found == -1:
        break

    swaprow(a, i, found)
    # now the pivot is in i

    for k in range(i+1, n):
        for l in range(m-1, j-1, -1):
            a[k][l] -= a[k][j]/a[i][j]*a[i][l]

    j += 1

for i in range(n-1, -1, -1):
    z = -1
    for j in range(m):
        if a[i][j] != 0:
            z = j
            break

    if z == -1:
        continue

    nonzeros = 0
    for j in range(m-1, z-1, -1):
        if a[i][j] != 0:
            nonzeros += 1
        a[i][j] /= a[i][z];

    # print("Nonzeros {}".format(nonzeros))
    assert (nonzeros < 3)

    for j in range(i):
        a[j][m-1] -= a[j][z]*a[i][m-1]
        a[j][z] = Fraction(0, 1)

"""
for i in range(n):
    s = ""
    for x in a[i]:
        s += '{} '.format(x)
    print(s)
"""

largest = 0
f = [0 for x in range(n)]
for i in range(n-1, -1, -1):
    f[i] = a[i][m-1]
    if largest == 0 and f[i] != 0:
        largest = i

if largest == 0:
    outfile = open("fygon.out", "w")
    outfile.write(str(f[0]))
    # print(str(f[0]))
    exit(0)

ans = ""
for i in range(largest-1):
    ans += "n*("

ans += str(f[largest]) + "*n"
for i in range(largest-1, 0, -1):
    if f[i] != 0:
        if f[i] >= 0:
            ans += "+"
        ans += str(f[i])
    ans += ")"

if f[0] != 0:
    if f[0] >= 0:
        ans += "+"
    ans += str(f[0])

outfile = open("fygon.out", "w")
outfile.write(ans)
# print(ans)
