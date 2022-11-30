import sys
tt=1
for l in sys.stdin:
    n=int(l)
    x=3**(n+1)//2**n
    ans=len(str(x))
    print(f"Case {tt}: {ans}")
    tt+=1
