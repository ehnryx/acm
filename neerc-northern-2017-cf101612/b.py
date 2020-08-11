infile = open("boolean.in", "r")
s = infile.readline()
v = s.strip().split('|')

allv = set()
pos = set()
neg = set()
for var in v:
    cur = var[-1]
    allv.add(cur)
    if len(var) == 1:
        pos.add(cur)
    else:
        neg.add(cur)

f = 1
cnt = 0
for var in allv:
    if var in pos and var in neg:
        f *= 2
    else:
        cnt += 1

outfile = open("boolean.out", "w")
ans = f * 2**cnt if f > 1 else 2**cnt - 1
outfile.write('{}\n'.format(ans))
