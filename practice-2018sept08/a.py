from sys import stdin
_ = stdin.readline()
for line in stdin:
    a,b = map(int, line.split())
    print(a*b)
print(" ")
