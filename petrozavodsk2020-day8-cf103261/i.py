from math import gcd

def calc(a, b):
    if gcd(a, b) == 1:
        return a
    if a == b:
        return a * b
    res = a
    while b % 2 == 0:
        b /= 2
        res *= 2
    if a == 2:
        res *= 2
    return res

d, k = [int(x) for x in input().split()]

"""
bf = 0
for a in range(1, 1789):
    bf = gcd(bf, (a+d)**k - a**k)
print(bf)
"""

twos = 1
while d % 2 == 0:
    twos *= 2
    d //= 2

ans = d * calc(twos, k)
print(d, calc(twos, k))
g = gcd(d, k)
while g > 1:
    ans *= g
    k //= g
    g = gcd(d, k)

print(ans)

#assert(ans == bf)

