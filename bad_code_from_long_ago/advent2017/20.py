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

vis = set()
p = [[], [], []]
v = [[], [], []]
a = [[], [], []]
cnt = 0
for line in stdin:
	vis.add(cnt)
	cnt += 1
	tp, tv, ta = line.split()
	tp = map(int, tp.split(','))
	tv = map(int, tv.split(','))
	ta = map(int, ta.split(','))
	
	for i in range(0, 3):
		p[i].append(tp[i])
		v[i].append(tv[i])
		a[i].append(ta[i])

t = 0
while t < 1000:
	t += 1
	for i in range(0, 3):
		for j in vis:
			v[i][j] += a[i][j]
			p[i][j] += v[i][j]

	bad = set()
	for j in vis:
		if j in bad:
			continue
		erase = []
		for k in vis:
			if j == k:
				continue
			if p[0][j] == p[0][k] and p[1][j] == p[1][k] and p[2][j] == p[2][k]:
				erase.append(k)
		if len(erase) > 0:
			erase.append(j)
			for r in erase:
				bad.add(r)
	for r in bad:
		vis.remove(r)

print len(vis)
