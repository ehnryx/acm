### START FAST IO ###
import os
os_input = os.read(0, int(1e7)).split()
os_input_pos = -1
answer_list = []
def read_s():
  global os_input_pos
  os_input_pos += 1
  return os_input[os_input_pos].decode()
def read_i():
  return int(read_s())
def write_s(v):
  answer_list.append(v)
def write_i(v):
  write_s(str(v))
def print_ans():
  os.write(1, "\n".join(answer_list).encode())
  os.write(1, "\n".encode())
#### END FAST IO ####

### START ITERATE RECURSION ###
from types import GeneratorType
def iterative(f, stack=[]):
  def wrapped_func(*args, **kwargs):
    if stack: return f(*args, **kwargs)
    to = f(*args, **kwargs)
    while True:
      if type(to) is GeneratorType:
        stack.append(to)
        to = next(to)
      else:
        stack.pop()
        if not stack: break
        to = stack[-1].send(to)
    return to
  return wrapped_func
#### END ITERATE RECURSION ####


import math

def gcd(a, b):
  if b == 0: return a
  return gcd(b, a % b)

T = read_i()
while T:
  T -= 1

  n = read_i()
  a = [n]
  for i in range(2, int(math.sqrt(n) + 1)):
    if n % i == 0:
      a.append(i)
      if i != n // i:
        a.append(n // i)

  a.sort()
  m = len(a)
  half = (m + 1) // 2
  res = [None for i in range(m)]
  res[::2] = a[:half]
  res[1::2] = reversed(a[half:])

  ans = 0
  for i in range(m):
    ans += (gcd(res[i], res[i-1]) == 1)
  write_s(' '.join([str(x) for x in res]))
  write_i(ans)

print_ans()

