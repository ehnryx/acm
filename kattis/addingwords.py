from sys import stdin, stdout
from collections import defaultdict
from random import sample

words = defaultdict(set)
value = defaultdict(int)

for line in stdin:
    vals = line.strip().split()
    if vals[0] == 'clear':
        words = defaultdict(set)
        value = defaultdict(int)
    elif vals[0] == 'def':
        v = int(vals[2])
        if vals[1] in value:
            words[value[vals[1]]].remove(vals[1])
        words[v].add(vals[1])
        value[vals[1]] = v
    else:
        n = (len(vals) - 1) // 2
        res = 0
        for i in range(n):
            if vals[2*i+1] not in value:
                res += 0x3f3f3f3f
            else:
                if i == 0 or vals[2*i] == '+':
                    res += value[vals[2*i+1]]
                else:
                    res -= value[vals[2*i+1]]
        if words[res]:
            stdout.write(' '.join(vals[1:]) + ' ' + sample(words[res], 1)[0] + '\n')
        else:
            stdout.write(' '.join(vals[1:]) + ' unknown\n')


