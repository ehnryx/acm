from math import *
from sys import stdin, stdout

N = 5000

f = [1]
for i in range(1,N+2):
    f.append(f[i-1] * i)

n = [1]
for i in range(1,N+1):
    n.append(n[i-1] * (2*i) * (2*i-1) // i)

stdin.readline()
for line in stdin:
    x = int(line)
    print(n[x]//f[x+1])
