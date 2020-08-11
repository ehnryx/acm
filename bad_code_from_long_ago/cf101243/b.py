f=open("input.txt","r")
g=open("output.txt","w")

n = int(f.readline())
ans = 2**(2*n//3-1)
if n % 2 == 0:
	ans += 2**(n//3-1)-1 #move first pile to middle peg
else:
	ans += 2**(n//3-1)-1 #move first pile to begin peg
	ans += 1 #move disk to middle pile
	ans += 2**(n//3-1)-1 #move first pile to middle pile
	ans -= 1 #... minus first disk
g.write(str(ans) + '\n')
