from itertools import permutations as p
a = sorted(list(set(p(sorted(input())))))
print(len(a))
for t in a:
  print(''.join(t))
