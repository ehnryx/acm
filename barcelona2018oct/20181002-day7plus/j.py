from sys import stdin

s = stdin.readline().strip()
a = int(s)
l = int(s[-1])

if a < 3:
  print("I'm sorry, Hexy")
else:
  b = k = 0
  if l%2 == 0:
    b = a-2
    k = (b**2)//4
  else:
    b = a-1
    k = (b**2)//2
  print(b+k, a+k)

