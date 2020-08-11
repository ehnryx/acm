from sys import stdin, stdout

T = int(stdin.readline())
for tt in range(T):
    n, k = [int(x) for x in stdin.readline().split()]
    a = [int(x) for x in stdin.readline().split()]
    for j in range(k):
        a[j::k] = sorted(a[j::k])
    for i in range(1, n):
        if a[i] < a[i-1]:
            stdout.write("no\n")
            break
    else:
        stdout.write("yes\n")

