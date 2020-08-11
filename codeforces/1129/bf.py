n = int(input())
a = [int(x) for x in input().split()]
res = 0
cur = 0
k = -1
for i in range(n):
    cur = cur+a[i]
    if cur<0:
        cur = 0
        k = i
    res = max(res, (i-k)*cur)
print(res, len(a)*sum(a))
print(len(a)*sum(a) - res)
