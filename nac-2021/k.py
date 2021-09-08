#
# brute force checker because i think we can pattern match
#

N = 7

# (x1, y1, x2, y2) => 1 if active player wins, 0 if they lose
x = {}

# presence of (x1, y1, x2, y2) means active player loses
xl = set([])

def solve(x1, y1, x2, y2):
    if (x1, y1) > (x2, y2):
        x1, y1, x2, y2 = x2, y2, x1, y1
    if (x1, y1, x2, y2) in xl:
        return 0
    # try reducing x1
    for a1 in range(1, x1):
        if solve(a1, y1, x2, y2) == 0:
            return 1
    # try reducing y1
    for b1 in range(1, y1):
        if solve(x1, b1, x2, y2) == 0:
            return 1
    # try reducing x2
    x2m = 1
    if y1 == y2:
        x2m = x1+1
    for a2 in range(x2m, x2):
        if (x1, y1) != (a2, y2) and solve(x1, y1, a2, y2) == 0:
            return 1
    # try reducing y2
    y2m = 1
    if x1 == x2:
        y2m = y1+1
    for b2 in range(y2m, y2):
        if (x1, y1) != (x2, b2) and solve(x1, y1, x2, b2) == 0:
            return 1
    # no possible win
    xl.add((x1, y1, x2, y2))
    return 0

"""
total # losses for NxN grid:
3 14
4 34
5 60
6 104
7 166
8 242
9 340
10 456
11 602
12 786
13 988
14 1236
15 1522
16 1838
17 2172
18 2568
19 3018
"""


for x1 in range(1,N+1):
    for y1 in range(1, N+1):
        print("for {} {}:".format(x1, y1))
        grid = []
        for i in range(N):
            grid.append(["."]*N)
        grid[x1-1][y1-1] = "!"
        for x2 in range(1, N+1):
            for y2 in range(1, N+1):
                if (x1, y1) >= (x2, y2):
                    continue
                #print(x1, y1, x2, y2, solve(x1, y1, x2, y2))
                if solve(x1, y1, x2, y2):
                    grid[x2-1][y2-1] = "*"
                    #pass
                else:
                    grid[x2-1][y2-1] = "x"
                    #print(x2, y2)
                    #pass
        for i in range(N):
            print(" ".join(grid[i]))