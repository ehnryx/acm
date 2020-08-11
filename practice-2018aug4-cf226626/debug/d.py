from sys import stdin, stdout

nm = list(map(lambda x: int(x), stdin.readline().split(' ')))
seenVals = {}
a = list(map(lambda x: int(x), stdin.readline().split(' ')))

lastDistinct = [0]*nm[0]
for i in range(nm[0]-1,-1,-1):
  if a[i] not in seenVals:
    seenVals[a[i]] = True
    lastDistinct[i] = 1
for i in range(nm[0]-2,-1,-1):
  lastDistinct[i] = lastDistinct[i] + lastDistinct[i+1]

l = []
for i in range(nm[1]):
  l.append(str(lastDistinct[int(stdin.readline()) - 1]))
stdout.write('\n'.join(l) + '\n')
