N = int(1e12)
print(N)
ans = (0, (0,0,0,0,0,0), 0)
stuff = []
for a in range(40):
  if (pa := 2**a) > N: break
  for b in range(30):
    if (pb := pa * 3**b) > N: break
    for c in range(24):
      if (pc := pb * 5**c) > N: break
      for d in range(12):
        if (pd := pc * 7**d) > N: break
        for e in range(9):
          if (pe := pd * 11**e) > N: break
          for f in range(9):
            if (pf := pe * 13**f) > N: break
            D = (a+1)*(b+1)*(c+1)*(d+1)*(e+1)*(f+1)
            ans = max(ans, (D, (a,b,c,d,e,f), pf))
            stuff.append((D, (a,b,c,d,e,f), pf))
print(ans)
print("\n".join(str(x) for x in sorted(stuff)))
#print("GOT", len(stuff))
#val = 0
#for x, _, __ in stuff:
#  val += x
#print("sum", val)
#print(val/len(stuff))
