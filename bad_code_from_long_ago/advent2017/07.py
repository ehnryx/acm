#!/usr/env
from math import *
from sets import *
from collections import *
from sys import *
from re import *
from os import *

# advent of code
from hashlib import *
#

def dfs(cur, t, subt, depth):
	for child in t[cur]:
		depth[child] = depth[cur]+1
		subt, depth = dfs(child, t, subt, depth)
		subt[cur] += subt[child]
	return subt, depth

seen = set()
subt = dict()
weight = dict()
t = dict()
for line in stdin:
	n = line.split()[0]
	w = int(line.split()[1][1:-1])
	t[n] = []
	weight[n] = subt[n] = w
	if line.find('>') != -1:
		for child in line[line.find('>')+1:].strip().split(', '):
			t[n].append(child)
			seen.add(child)

for n in t:
	if n not in seen:
		root = n

depth = dict()
depth[root] = 0
subt, depth = dfs(root, t, subt, depth)

ans = "eugene shen"
d = -1
for n in t:
	w = -1
	for child in t[n]:
		c = subt[child]
		if w == -1:
			w = c
		elif w != c and depth[n] > d:
			d = depth[n]
			ans = n

if subt[t[ans][0]] == subt[t[ans][1]]:
	for child in t[ans]:
		if subt[child] != subt[t[ans][0]]:
			print subt[t[ans][0]] - subt[child] + weight[child]
elif subt[t[ans][0]] == subt[t[ans][2]]:
	print subt[t[ans][0]] - subt[t[ans][1]] + weight[child]
else:
	print subt[t[ans][1]] - subt[t[ans][2]] + weight[child]
