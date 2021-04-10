from random import random

s = ''
a = [x for x in range(1, 51)]
for i in range(49, -1, -1):
  j = int(random()*i)
  x = a[i]
  y = a[j]
  a[i] = y
  a[j] = x
print(a)
print(''.join([str(x) for x in a]))
