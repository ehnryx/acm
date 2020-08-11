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

reg = defaultdict(int)

com = []
for line in stdin:
    com.append(line)

ans = 0

pc = 0
while pc >= 0 and pc < len(com):
    it, x, y = com[pc].split();
    if len(y) == 1 and y.isdigit() == False:
        y = reg[y]
    else:
        y = int(y)

    if it == "set":
        reg[x] = y
    elif it == "sub": 
        reg[x] -= y
    elif it == "mul":
        reg[x] *= y
        ans += 1
    elif it == "jnz":
        if len(x) != 1 or x.isdigit():
            x = int(x)
        else:
            x = reg[x]
        if x != 0:
            pc += y-1
    
    pc += 1

print ans



