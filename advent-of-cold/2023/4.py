import sys
#ans = 0
I = [L.strip() for L in sys.stdin]
c = [1] * (len(I) + 7)
for i, L in enumerate(I):
  _, L = L.strip().split(":")
  a, b = L.split("|")
  win = set(a.strip().split())
  tot = set(b.strip().split())
  #ans += 1 << len(win & tot) >> 1
  add = len(win & tot)
  for j in range(add):
    c[i + j+1] += c[i]
#print(ans)
print(sum(c[0:len(I)]))
