def get(s, i):
  if s[i].isdigit(): return int(s[i])
  if s[i:i+3] == "one": return 1
  if s[i:i+3] == "two": return 2
  if s[i:i+5] == "three": return 3
  if s[i:i+4] == "four": return 4
  if s[i:i+4] == "five": return 5
  if s[i:i+3] == "six": return 6
  if s[i:i+5] == "seven": return 7
  if s[i:i+5] == "eight": return 8
  if s[i:i+4] == "nine": return 9
  return None

import sys
ans = 0
for f in sys.stdin:
  f += "xxxxx"
  first, last = None, None
  for i in range(len(f) - 5):
    if digit := get(f, i):
      first = first or digit
      last = digit
  ans += first * 10 + last
print(ans)
