from sys import stdin, stdout

MOD = 1000003

stdin.readline()
for line in stdin:
	n, m = map(int, line.split())
	stdout.write(str((2**n + 2**m - 2) % MOD) + '\n')
