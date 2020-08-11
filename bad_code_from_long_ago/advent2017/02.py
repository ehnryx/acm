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

ans = 0
for line in stdin:
	a = map(int, line.split())
	for i in range(0, len(a)):
		for j in range(0, i):
			if a[i] % a[j] == 0:
				ans += a[i]/a[j]
			elif a[j] % a[i] == 0:
				ans += a[j]/a[i]
print ans

