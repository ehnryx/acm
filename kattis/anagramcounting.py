from sys import stdin, stdout
from collections import defaultdict
from math import factorial

for line in stdin:
    line = line.strip()
    cnt = defaultdict(int)
    for c in line:
        cnt[c] += 1
    ans = factorial(len(line))
    for k,v in cnt.items():
        ans //= factorial(v)
    stdout.write(str(ans)+'\n')
