import sys
from collections import deque
from sets import Set
import math

def main():
  cap = 10**72

  k, n = [int(x) for x in raw_input().split()]

  q = deque()
  seen = Set([0])

  ans = 0
  q.append([0,0,1])
  while True:
    cur = q.popleft()
    if cur[2] > cap: 
      continue
    t1 = cur[0]
    t2 = cur[1]
    t3 = cur[2]
    while t1 in seen or t2 in seen or t3 in seen:
      q.append([t1, t3, find(t1, t3, k)])
      t1 = t2
      t2 = t3
      t3 = find(t1, t2, k)
    if t3 < cap:
      sys.__stdout__.write(str(t1) + " " + str(t2) + " " + str(t3) + "\n")
      ans += 1
      if ans == n:
        return
      seen.add(t1)
      seen.add(t2)
      seen.add(t3)

def find(a, b, k):
  B = k*(a+b)
  first = 4*(a*a + b*b)
  second = 4*(k*a*b + 1)
  D = B*B - first + second
  left = 10**(int(math.floor(math.log(max(1, B*B - first), 10) / 2)))
  right = 10**(int(math.ceil(math.log(B*B + second, 10) / 2)))
  while left <= right:
    mid = (left+right)/2
    cur = mid*mid
    if cur == D:
      return (B + mid)/2
    elif cur > D:
      right = mid-1
    else:
      left = mid+1

main()
