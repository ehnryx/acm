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

state = [ dict(), dict() ]
trans = [ dict(), dict() ]
dir = [ dict(), dict() ]

raw_input()
lim = int(raw_input().split()[-2])

for i in range(0, 6):
	cur = chr(ord('A')+i)
	raw_input()
	raw_input()
	raw_input()
	trans[0][cur] = int(raw_input().split()[-1][:-1])
	dir[0][cur] = raw_input().split()[-1][:-1]
	state[0][cur] = raw_input().split()[-1][0]
	raw_input()
	trans[1][cur] = int(raw_input().split()[-1][:-1])
	dir[1][cur] = raw_input().split()[-1][:-1]
	state[1][cur] = raw_input().split()[-1][0]
	
ans = 0

tape = defaultdict(int)
curst = 'A'
pc = 0
cnt = 0
while cnt < lim:
	cnt += 1
	ntrans = trans[tape[pc]][curst]
	nstate = state[tape[pc]][curst]
	ndir = dir[tape[pc]][curst]

	ans += ntrans - tape[pc]
	tape[pc] = ntrans
	curst = nstate
	if ndir == "right":
		pc += 1
	else:
		pc -= 1

print ans



