import sys
import collections
ans = 0
for L in sys.stdin:
  game, vals = L.split(":")
  A = collections.defaultdict(int)
  for turn in vals.split(";"):
    tks = turn.split(",")
    for kv in tks:
      v, k = kv.split()
      A[k] = max(A[k], int(v))
  val = 1
  for k, v in A.items():
    val *= v
  ans += val
print(ans)
