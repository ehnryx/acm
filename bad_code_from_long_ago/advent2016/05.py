from math import *
from sets import *
from collections import *
from sys import *
from re import *
from os import *

# advent of code
from hashlib import md5
#

n = raw_input()
i = 0
c = 0
ans = ['-']*8
while c < 8:
  s = md5(n + str(i)).hexdigest()
  i += 1
  if s[:5] == "00000":
    if s[5].isdigit() and int(s[5]) < 8 and ans[int(s[5])] == '-':
      ans[int(s[5])] = s[6]
      print i
      c += 1
print ''.join(ans)

