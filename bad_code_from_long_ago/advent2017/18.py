#!/usr/env
from math import *
from decimal import *
from sets import *
from collections import *
from sys import *
from re import *
from os import *

# advent of code
from hashlib import *
#

ans = 0

reg = [defaultdict(int), defaultdict(int)]
reg[0]['p'] = 0
reg[1]['p'] = 1

lines = []
for line in stdin:
	lines.append(line)

q = [deque(), deque()]
pc = [0, 0]
deadlock = 0
id = 0
while id < 0x3f3f3f3f3f:
	id += 1
	i = id%2
	count = 0
	while pc[i] >= 0 and pc[i] < len(lines):
		count += 1
		a = lines[pc[i]].split()
		if a[0] == "snd":
			if i == 1:
				ans += 1
			if a[1].isdigit() or (len(a[1]) > 1 and a[1][1:].isdigit()):
				q[i^1].append(int(a[1]))
			else:
				q[i^1].append(reg[i][a[1]])
		elif a[0] == "set":
			if a[2].isdigit() or (len(a[2]) > 1 and a[2][1:].isdigit()):
				reg[i][a[1]] = int(a[2])
			else:
				reg[i][a[1]] = reg[i][a[2]]
		elif a[0] == "add":
			if a[2].isdigit() or (len(a[2]) > 1 and a[2][1:].isdigit()):
				reg[i][a[1]] += int(a[2])
			else:
				reg[i][a[1]] += reg[i][a[2]]
		elif a[0] == "mul":
			if a[2].isdigit() or (len(a[2]) > 1 and a[2][1:].isdigit()):
				reg[i][a[1]] *= int(a[2])
			else:
				reg[i][a[1]] *= reg[i][a[2]]
		elif a[0] == "mod":
			if a[2].isdigit():
				reg[i][a[1]] %= int(a[2])
			else:
				reg[i][a[1]] %= reg[i][a[2]]
		elif a[0] == "rcv":
			if len(q[i]) == 0:
				break
			reg[i][a[1]] = q[i].popleft()
		else:
			x,y = 0,0
			if a[1].isdigit() or (len(a[1]) > 1 and a[1][1:].isdigit()):
				x = int(a[1])
			else:
				x = reg[i][a[1]]
			if a[2].isdigit() or (len(a[2]) > 1 and a[2][1:].isdigit()):
				y = int(a[2])
			else:
				y = reg[i][a[2]]
			if x > 0:
				pc[i] += y - 1
			
		pc[i] += 1
	if count == 1:
		deadlock += 1
	else:
		deadlock = 0
	if deadlock > 2:
		break

print ans



