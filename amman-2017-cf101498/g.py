from sys import stdin, stdout
from math import gcd

cap = int(2e12)

T = int(stdin.readline(), 10)
while T > 0:
	T -= 1

	n = int(stdin.readline(), 10)
	arr = [ int(x, 10) for x in stdin.readline().split() ]

	ans = 0
	i = 0
	while i < n:
		sum = 0
		lcm = 1
		j = i
		while j < n:
			if lcm > cap:
				break
			lcm = lcm*arr[j] // gcd(lcm,arr[j])
			sum += arr[j]
			if sum % lcm == 0:
				ans += 1
			j += 1
		i += 1

	stdout.write(str(ans) + '\n')

