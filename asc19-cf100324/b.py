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


infile = open("cartesian.in", "r")
outfile = open("cartesian.out", "w")

n = int(infile.readline())
adj = [[] for i in range(n)]
for i in range(n):
  l, r = [int(x) - 1 for x in infile.readline().split()]
  if l >= 0:
    adj[i].append(l)
  if r >= 0:
    adj[i].append(r)

ncr = [[0 for i in range(j+1)] for j in range(n+1)]
for i in range(n+1):
  ncr[i][0] = ncr[i][i] = 1
  for j in range(1, i):
    ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1]

@iterative
def solve(u):
  res = 1
  sz = 1
  child = 0
  for v in adj[u]:
    vres, vsz = yield solve(v)
    res *= vres
    sz += vsz
    child = vsz
  yield res * ncr[sz-1][child], sz

outfile.write("{}\n".format(solve(0)[0]))


