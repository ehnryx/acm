import os, sys

### START FAST INPUT ###
inp = os.read(0, int(1e7)).split()
inp_pos = -1
def cin():
    global inp_pos
    inp_pos += 1
    return inp[inp_pos]
#### END FAST INPUT ####

T = int(cin())

ans = []
for tt in range(T):
    n = int(cin())
    a, b = [], []
    for i in range(n):
        a.append(int(cin()))
        b.append(int(cin()))
    minv = 0x3f3f3f3f3f3f3f3f
    total = 0
    for i in range(n):
        j = i-1 if i > 0 else n-1
        total += max(0, a[i] - b[j])
        minv = min(minv, a[i], b[j])
    ans.append(str(total + minv).encode())
os.write(1, "\n".encode().join(ans))

