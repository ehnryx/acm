import sys

ans=0
for line in sys.stdin:
    L=[None for i in range(10)]
    a = [''.join(sorted(x)) for x in line.strip().split()]
    print(a)
    for x in a:
        L[len(x)] = x;
    seen=0
    cur=0
    for x in a:
        if len(x) == 1:
            seen=1
        elif len(x) == 2:
            cur=cur*10+seen*1
        elif len(x) == 4:
            cur=cur*10+seen*4
        elif len(x) == 3:
            cur=cur*10+seen*7
        elif len(x) == 7:
            cur=cur*10+seen*8
        elif len(x) == 5:
            ok = 1
            for k in L[3]:
                if k not in x:
                    ok = 0
            if ok:
                cur=cur*10 + seen*3
                continue
            ok=0
            for k in L[4]:
                if k in x:
                    ok+=1
            if ok==3:
                cur=cur*10+seen*5
                continue
            else:
                cur=cur*10+seen*2
        elif len(x) == 6:
            c = '0'
            for k in 'abcdefg':
                if k not in x:
                    c=k
            if c in L[2]:
                cur=cur*10+seen*6
            elif c in L[4]:
                cur=cur*10+seen*0
            else:
                cur=cur*10+seen*9
    ans+=cur

print(ans)
