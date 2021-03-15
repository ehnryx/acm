from random import random
print(300000)
a = ''
for i in range(300000):
  a += chr(ord('a')+int(random()*26))
print(a)
