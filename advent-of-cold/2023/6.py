import sys
I = [L.strip() for L in sys.stdin]
t = int("".join(I[0].split()[1:]))
d = int("".join(I[1].split()[1:]))
ans = 1
c = 0
for i in range(t):
  c += (i * (t-i) > d)
ans *= c
print(ans)
