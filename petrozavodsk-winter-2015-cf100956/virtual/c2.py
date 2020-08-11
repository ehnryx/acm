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

for i in range(n):
  for j in range(m):
    g = gcd(a[i],b[j])
    a[i] //= g
    b[j] //= g

stderr.write('precompute: {}\n'.format(clock()))

ans = []
q = int(stdin.readline())
for i in range(q):
  mod = int(stdin.readline())
  res = 1
  for v in b:
    if gcd(v,mod) != 1:
      ans.append('DIVISION BY ZERO')
      break
    inv,_ = egcd(v,mod)
    res = (res*(inv+mod)) % mod
  else:
    for v in a:
      res = (res*v) % mod
    ans.append(str(res))
stdout.write('\n'.join(ans))
stdout.write('\n')
