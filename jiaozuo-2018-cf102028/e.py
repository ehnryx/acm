from sys import stdin, stdout

def gcd(a,b):
    if a==0:
        return b
    elif b==0:
        return a
    else:
        return gcd(b, a%b)

N = 1000
primes = []
for i in range(2,N):
    for j in range(2,i):
        if i%j == 0:
            break
    else:
        primes.append(i)

T = int(stdin.readline())
for i in range(T):
    m = int(stdin.readline())
    n = 1
    d = 1
    tot = 1
    for p in primes:
        tot *= p
        if tot > m:
            break
        n *= p
        d *= p+1
    g = gcd(n,d)
    stdout.write(str(n//g)+'/'+str(d//g)+'\n')
