FNAME = 'ideal'

inn = open(FNAME + '.in', 'r')
out = open(FNAME + '.out', 'w')

lines = inn.read().split('\n')

def nb_line(line):
    for c in line:
        if (c != ' '):
            return True
    return False

lines = list(filter(nb_line, lines))

while (len(lines[-1]) == 0):
    # remove empty space at end
    lines = lines[:-1]

def all_false(row):
    for v in row:
        if (v):
            return False
    return True

def all_true(row):
    for v in row:
        if (not v):
            return False
    return True

def isLine(x):
    for c in x:
        if (c != '-' and c != ' '):
            return False
    return True

def readHeader(x):
    indent = 4
    while (x[indent] == ' '):
        indent += 1
    probs = x[indent:]
    cnt = 0
    for c in probs:
        if (c == '='):
            break
        if (c != ' '):
            cnt += 1
    return cnt

sline = len(lines)-1
while not isLine(lines[sline]):
    sline -= 1

P = readHeader(lines[sline-1])
T = len(lines) - sline - 1

solve_cnt = []
rank = []
table = []
for line in lines[sline+1:]:
    tok = list(filter(lambda x: len(x) != 0, line.split(' ')))
    tok = tok[-(P+3):]
    table.append(list(map(lambda x: x[0] == '+', tok[:P])))
    solve_cnt.append(int(tok[P]))
    rank.append(int(tok[P+2]))

def calcO(table):
    cnt = 0
    for row in table:
        if (all_true(row)):
            cnt += 1
    return cnt / T

def calcV(table):
    cnt = 0
    for row in table:
        if (all_false(row)):
            cnt += 1
    return cnt / T

def calcE(n_solves):
    prev = n_solves[0]
    ans = 0
    for num in n_solves:
        if (prev > num + 1 ):
            ans += prev-num-1
        prev = num
    return ans

def calcU(table):
    cnt = 0
    for i in range(P):
        good = False
        for row in table:
            if row[i]:
                good = True
                break
        if (not good):
            cnt += 1
    return cnt/P

def calcI(table, p):
    cnt = 0
    ans = 0
    add = 0
    prev = 1
    for i in range(len(table)):
        row = table[i]
        if (prev != rank[i]):
            cnt += add
            add = 0
        if (row[p]):
            ans = cnt
        else:
            add += 1
        prev = rank[i]
    return ans/T

if(P == 0 or T == 0):
    while True:
        pass

_V = calcV(table)
_O = calcO(table)
_E = calcE(solve_cnt) / P
_U = calcU(table)
# print('Vainness = %.3f' % _V)
# print('Oversimplification = %.3f' % _O)
# print('Evenness = %.3f' % _E)
# print('Unsolvability = %.3f' % _U)
out.write('Vainness = %.3f\n' % _V)
out.write('Oversimplification = %.3f\n' % _O)
out.write('Evenness = %.3f\n' % _E)
out.write('Unsolvability = %.3f\n' % _U)
sum_I = 0
for i in range(P):
    val = calcI(table, i)
    sum_I += val
    # print('Instability %d = %.3f' % (i+1, val))
    out.write('Instability %d = %.3f\n' % (i+1, val))
sum_I /= P

_N = 1.03 * _V + 3.141 * _O + 2.171 * _E + 1.414 * _U + sum_I
# print('Negidealness = %.3f\n' % _N)
out.write('Negidealness = %.3f\n' % _N)
