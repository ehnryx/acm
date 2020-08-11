ans = dict()
op = ['+','-','*','/']
for i in op:
    for j in op:
        for k in op:
            s = '4 '+i+' 4 '+j+' 4 '+k+' 4'
            v = eval(s)
            if v not in ans:
                ans[v] = s + ' = ' + str(v)

T = int(input())
for i in range(T):
    n = int(input())
    if n in ans:
        print(ans[n])
    else:
        print("no solution")
