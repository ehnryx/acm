p = input
for z in range(int(p())):
    p()
    r = 0
    for x in p().split():
        r ^= int(x) % 4
    print("first" if r else "second")
