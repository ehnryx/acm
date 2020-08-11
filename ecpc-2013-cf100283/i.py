def gcd(a,b):
    while b != 0:
        a,b = b,a%b
    return a
def lcm(a,b):
    return a*b//gcd(a,b)

res = 1
for i in range(2,13+1):
    res = lcm(res,i)
print(res)

