import re

s = input()
pattern = ""
for c in s:
	if c == '*':
		pattern += '.'
	elif c == '.':
		pattern += '\\'
	pattern += c
pattern = re.compile(pattern)

n = int(input())
for i in range(0, n):
	t = input()
	if pattern.fullmatch(t) is not None:
		print(t)
