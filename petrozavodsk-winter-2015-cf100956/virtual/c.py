from sys import stdin, stdout, stderr
from time import clock

def gcd(a,b):
  while b:
    a,b = b,a%b
  return a

def egcd(a,b):
  if b == 0:
    return 1,0
  else:
    y,x = egcd(b, a%b)
    y -= x * (a//b)
    return x,y

n,m = map(int,stdin.readline().split())
a = [int(x) for x in stdin.readline().split()]
b = [int(x) for x in stdin.readline().split()]

A = 1
for v in a:
  A *= v
B = 1
for v in b:
  B *= v
stderr.write('{} {}\n'.format(A,B))

stderr.write('precompute: {}\n'.format(clock()))

ans = []
q = int(stdin.readline())
for i in range(q):
  mod = int(stdin.readline())
stdout.write('\n'.join(ans))
stdout.write('\n')
