from sys import stdout

def ziginv(x):
    if x % 2 == 1:
        return -(x/2)-1
    else:
        return x/2

def zig(x):
    if x >= 0:
        return 2*x
    else:
        return -2*x-1

n = int(raw_input())

x = map(int, raw_input().split(' '))
cur = 0
mul = 1
for i in x:
    if i >= 128:
        cur += (i-128) * mul
        mul *= 2**7
    else:
        cur += i * mul
        stdout.write(str(ziginv(cur)) + '\n')
        cur = 0
        mul = 1
