import sys
I = [L.strip() for L in sys.stdin]
#mp = {}
key = -1
mp = [[] for _ in range(9)]
for L in I:
  if not L: continue
  if L.startswith("seeds:"):
    ss = [int(x) for x in L.split()[1:]]
  elif L.endswith("map:"):
    #key = L.split()[0]
    #mp[key] = []
    key += 1
  else:
    mp[key].append([int(x) for x in L.split()])
assert ss

ranges = []
for i in range(0, len(ss), 2):
  ranges.append((ss[i], ss[i] + ss[i+1] - 1))
for m in mp:
  if not m: continue
  nr = []
  for a, b, c in m:
    cr = []
    for l, r in ranges:
      if b + c - 1 < l or r < b:
        cr.append((l, r))
      elif b <= l and r <= b + c - 1:
        nr.append((a + l - b, a + r - b))
      elif l < b and b + c - 1 < r:
        cr.append((l, b - 1))
        cr.append((b + c, r))
        nr.append((a, a + c - 1))
      elif l < b:
        cr.append((l, b - 1))
        nr.append((a, a + r - b))
      elif b + c - 1 < r:
        cr.append((b + c, r))
        nr.append((a + l - b, a + c - 1))
      else:
        assert False
    ranges = cr
  ranges = nr
print(ranges)
print(min(ranges)[0])
