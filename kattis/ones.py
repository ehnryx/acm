from sys import stdout
tot = 100000+1
ans = []
ans.append(str(0))
for n in range(1,tot):
    if n%2 != 0 and n%5 != 0:
        s = 1
        while s%n != 0:
            s = 10*s + 1
        ans.append(str(len(str(s))))
stdout.write('\n'.join(ans)+'\n')
