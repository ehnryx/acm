l, r = [int(x) for x in input().split()]
print((r*(r+1)//2 - l*(l-1)//2) % 9)
