from collections import deque
from sets import Set
import math

def main():
	cap = 10**61
	midcap = 10**27

	k, n = [int(x) for x in raw_input().split()]

	q = deque()
	seen = Set([0])

	ans = 0
	q.append([0,0,1])
	while True:
		cur = q.popleft()
		t1 = cur[0]
		t2 = cur[1]
		t3 = cur[2]
		while t1 in seen or t2 in seen or t3 in seen:
			t1 = t2
			t2 = t3
			t3 = find(t1, t2, k)
		if t3 < cap:
			print str(t1) + " " + str(t2) + " " + str(t3)
			ans += 1
			if ans == n:
				return
			seen.add(t1)
			seen.add(t2)
			seen.add(t3)

			t4 = find(t2, t3, k)
			if t4 < cap:
				q.append([t2, t3, t4])
			t1 = cur[0]
			t2 = cur[2]
			t3 = find(t1, t2, k)
			while t3 < midcap:
				q.append([t1, t2, t3])
				t1 = t2
				t2 = t3
				t3 = find(t1, t2, k)

def find(a, b, k):
	B = k*(a+b)
	first = 4*(a*a + b*b)
	second = 4*(k*a*b + 1)
	D = B*B - first + second
	if D < 100000000000:
		return (B + int(math.sqrt(D)))/2
	else:
		left = 10**(int(math.floor(math.log(max(1, B*B - first/2), 10) / 2)))
		right = 10**(int(math.ceil(math.log(B*B + second/2, 10) / 2)))
		while left <= right:
			mid = (left+right)/2
			cur = mid*mid
			if cur == D:
				return (B + mid)/2
			elif cur > D:
				right = mid-1
			else:
				left = mid+1
		while True:
			print "sad :("

main()
