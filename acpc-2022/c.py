from math import factorial

n = int(input())
ans = 0
for i in range(1, n+1):
    ans += factorial(n) // factorial(n-i)

if ans > int(1e9):
    print("JUST RUN!!")
else:
    print(ans)
