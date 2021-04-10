from sys import stdin, stdout, stderr
#from math import log
from random import randint

N = int(1e5+10)
ps = []
isp = [True for i in xrange(N)]
for i in xrange(2, N):
    if i*i > N:
        break
    if isp[i]:
        for j in xrange(i*i, N, i):
            isp[j] = False
for i in xrange(2, N):
     if isp[i]:
         ps.append(i)

def egcd(a, b):
    if b == 0:
        return (1, 0)
    y, x = egcd(b, a%b)
    y -= x * (a//b)
    return x, y

def chin_rem(a1, m1, a2, m2):
    X1, X2 = egcd(m1, m2)
    M = m1*m2
    return (((X1*m1*a2 + X2*m2*a1 + a1)%M + M)%M, M)

T = int(stdin.readline())
for tt in xrange(1, T+1):
    n = int(stdin.readline())
    if n <= 6:
        stdout.write('Case {}: {}\n'.format(tt, -1))
    else:
        bad = set(range(1, n+1))
        curi = 0
        rem = 0
        mod = 1
        while bad:
            p = ps[curi]
            if p > n:
                #stderr.write('bad: {}\n'.format(bad))
                stdout.write('Case {}: {}\n'.format(tt, -1))
                break
            buckets = [0 for i in xrange(p)]
            for i in bad:
                buckets[i % p] += min(i, n - i)
            best = 0
            besti = 0
            for i in xrange(p):
                if buckets[i] > best:
                    best = buckets[i]
                    besti = i
            rem, mod = chin_rem(rem, mod, besti, p)
            toremove = []
            for i in bad:
                if (i - p >= 1 or i + p <= n) and i % p == besti:
                    toremove.append(i)
            #stderr.write('remove: {}\n'.format(toremove))
            bad.difference_update(toremove)
            curi += 1
        if not bad:
            stdout.write('Case {}: {}\n'.format(tt, rem))
            stderr.write('{}\n'.format(curi))
