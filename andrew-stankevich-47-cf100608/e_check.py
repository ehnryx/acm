from sys import stdin

lim = int(1e18)

grid = []
for line in stdin:
	grid.append(map(int, line.strip().split()))

n = len(grid)
diff = set()
vals = set()
for i in range(0, n):
	a = b = 1
	for j in range(0, n):
		a *= grid[i][j]
		b *= grid[j][i]
		if grid[i][j] > lim:
			print(str(grid[i][j]) + " too large")
		if grid[i][j] in vals:
			print("("+str(i)+","+str(j)+") in set " + str(grid[i][j]))
		vals.add(grid[i][j])
	diff.add(a)
	diff.add(b)

if len(diff) != 1:
	print("not working on " + str(n))
else:
	print("done checking " + str(n))
