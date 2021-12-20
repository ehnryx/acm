from collections import deque, defaultdict
from itertools import product, permutations, accumulate
from itertools import zip_longest, groupby, takewhile
from heapq import heappush, heappop, heapify, merge
import sys
big = 1999999999999999999
IN = [ x.strip() for x in sys.stdin ]

g = []
for r in IN:
  if len(r) < 2:
    continue
  if ',' not in r:
    g.append([])
    continue

  a, b, c = [int(x) for x in r.split(',')]
  g[-1].append((a,b,c))

rotations = []
for i in range(6):
  for j in range(4):
    rotations.append((i,j))

def rotate(_v, R):
  v = [x for x in _v]

  if R[0] == 1:
    v[0] = -v[0]
    v[1] = -v[1]
  elif R[0] == 2:
    v[1], v[0] = v[0], -v[1]
  elif R[0] == 3:
    v[0], v[1] = v[1], -v[0]
  elif R[0] == 4:
    v[2], v[0] = v[0], -v[2]
  elif R[0] == 5:
    v[0], v[2] = v[2], -v[0]

  if R[0] <= 1:
    if R[1] == 1:
      v[1] = -v[1]
      v[2] = -v[2]
    elif R[1] == 2:
      v[1], v[2] = v[2], -v[1]
    elif R[1] == 3:
      v[2], v[1] = v[1], -v[2]
  elif R[0] <= 3:
    if R[1] == 1:
      v[0] = -v[0]
      v[2] = -v[2]
    elif R[1] == 2:
      v[0], v[2] = v[2], -v[0]
    elif R[1] == 3:
      v[2], v[0] = v[0], -v[2]
  else:
    if R[1] == 1:
      v[0] = -v[0]
      v[1] = -v[1]
    elif R[1] == 2:
      v[0], v[1] = v[1], -v[0]
    elif R[1] == 3:
      v[1], v[0] = v[0], -v[1]


  return v

def undo(R):
  v = [1,2,3]
  for T in rotations:
    if v == rotate(rotate(v,R),T):
      #assert(v == rotate(rotate(v,T),R))
      return T
  assert(False)

def compose(R,T):
  v = [1,2,3]
  for X in rotations:
    if rotate(v,X) == rotate(rotate(v,R),T):
      return X
    ##print(X,"vs",R,T,"->",rotate(v,X)," : ",rotate(rotate(v,R),T))
  ##print("BAD",R,T)
  assert(False)

#print(list(rotate((1,2,3), r) for r in rotations))

uid = len(g)
head = list(range(len(g)))

#print(len(g))
adj = defaultdict(list)
for i in range(len(g)):
  print("DO",i)
  for j in range(i):
    if head[i] != -1 and head[i] == head[j]:
      continue

    ok = False
    for R in rotations:
      ##print(i,j,R)
      ng = [rotate(x, R) for x in g[j]]
      for ii in range(len(g[i])):
        for jj in range(len(g[j])):
          da,db,dc = ng[jj][0]-g[i][ii][0],  ng[jj][1]-g[i][ii][1],  ng[jj][2]-g[i][ii][2]
          cnt = 0
          s = set(g[i])
          for v in ng:
            if (v[0]-da,v[1]-db,v[2]-dc) in s:
              cnt += 1
          if cnt >= 12:
            ok = True
            break
        if ok:
          break
      if ok:
        break

    if ok:
      ##print("i,j",i,j)

      adj[i].append((j, R, (da,db,dc)))

      T = undo(R)
      v = rotate(g[i][ii],T)
      da,db,dc = v[0]-g[j][jj][0],  v[1]-g[j][jj][1],  v[2]-g[j][jj][2]
      adj[j].append((i, T, (da,db,dc)))

      uid += 1
      x, y = head[i], head[j]
      for kk in range(len(g)):
        if head[kk] == x or head[kk] == y:
          head[kk] = uid

#print("HERE")
#exit()
print(head)

mR = [None] * len(g)
mD = [None] * len(g)

mR[0] = (0,0)
mD[0] = (0,0,0)

bfs = []
bfs.append(0)
while len(bfs) > 0:
  i = bfs[-1]
  bfs.pop()
  #print("BFS",i)
  for j, R, (da,db,dc) in adj[i]:
    if mD[j] is not None:
      continue
    ##print("compose",R,mR[i],"->",compose(R,mR[i]))
    mR[j] = compose(R, mR[i])
    D=rotate((da,db,dc), mR[i])
    mD[j] = (mD[i][0]-D[0], mD[i][1]-D[1], mD[i][2]-D[2])
    bfs.append(j)

#print(mD, mR)

S = set()
for i,r in enumerate(g):
  for x,y,z in r:
    v = rotate([x,y,z], mR[i])
    S.add((v[0]+mD[i][0], v[1]+mD[i][1], v[2]+mD[i][2]))

#print(S)
print(len(list(S)))


ans=0
for i in range(len(g)):
  I = rotate((0,0,0),mR[i])
  for j in range(len(g)):
    J = rotate((0,0,0),mR[j])
    ans = max(ans, sum([abs(I[k]+mD[i][k] - (J[k]+mD[j][k])) for k in range(3)]))
print(ans)
