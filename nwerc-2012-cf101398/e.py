from sys import stdin, stdout

lucas = [2, 1]
for i in range(2, 10000 + 1):
  lucas.append(lucas[i-2] + lucas[i-1])

for line in stdin:
  stdout.write(str(lucas[int(line)]) + '\n')
