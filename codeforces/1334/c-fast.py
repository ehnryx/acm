import os, sys

pos = 0
inp = os.read(0, int(1e7)).split()

T = int(inp[pos])
pos += 1

ans = []
tt = 0
while tt < T:
    n = int(inp[pos])
    pos += 1
    i = 0
    minv = 0x3f3f3f3f3f3f3f3f
    total = 0
    while i < n:
        a = int(inp[pos])
        pos += 1
        b = int(inp[pos])
        pos += 1
        if i == 0:
            firsta = a
        else:
            total += max(0, a - pb)
        minv = min(minv, a, b)
        pb = b
        i += 1
    total += max(0, firsta - b)
    ans.append(str(total + minv).encode("ascii"))
    tt += 1
os.write(1, "\n".encode().join(ans))
