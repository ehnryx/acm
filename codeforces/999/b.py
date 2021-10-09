n = int(input())
t = input()

s = []
for c in t:
  s.append(c)
print(s)

for i in range(1,n):
  if n%i==0:
    d=n//i
    r = s[0:d:-1]
    for j in range(0,d):
      s[j] = r[j]

print(''.join(s))
