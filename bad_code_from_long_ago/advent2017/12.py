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

w = [0]*2000
r = [-1]*2000

def weight(n):
	global w
	return w[n]

def find(n):
	global r
	if r[n] == -1:
		return n
	else:
		r[n] = find(r[n])
		return r[n]

def link(a, b):
	global r
	global w
	a = find(a)
	b = find(b)
	if a != b:
		if w[a] < w[b]:
			t = a
			a = b
			b = t
		w[a] += w[b] + 1
		r[b] = a

for line in stdin:
	par = line.split()
	n = int(par[0])
	for id in par[2:]:
		link(n, int(id.split(',')[0]))

s = set()
for i in range(0, 2000):
	s.add(find(i))

print len(s)
