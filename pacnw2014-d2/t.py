import re
number = "(0|[-]?[1-9][0-9]*)"
pattern = re.compile("^" + number + "[-+*]" + number + "=" + number + "$")

T = int(input())
while T:
  T -= 1
  line = input()
  for d in range(10):
    if str(d) in line:
      continue
    check = line.replace('?', str(d))
    left, right = check.split('=')
    if pattern.match(check) and eval(left) == int(right):
      print(d)
      break
  else:
    print(-1)
