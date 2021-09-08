/*

a_i & x = x => bits in a_i are superset of x

=> for every a_i, all bit-subsets of a_i exist in a


if we just start with the integers with max # bits will that run in time??
i think the solution guarantee provides a bound 
(ya but there are (60 choose 30)/ n  possible integers with max # bits)

maybe greedy works?? match highest-bitcount numbers with lowest-bitcount numbers
greedy by matching highest-bitcount numbers with highest bitcount numbers that match

find a bipartite matching on a graph defined by:
a_i => every a_j where a_i & a_j = 0


A, B are maximal
a subset A\C and b subset B\C
c subset C = A intersect B

A\C + C\c <--> c (in A)
B\C + C\c <--> c (in B)
A\C + c <--> C\c
B\C + c <--> C\c

A\C + C\c ~~ B\C + c
A\C + c ~~ B\C + C\c (in A + B)
C\c ~~ c (in C)

(add third)
common: in C, 

D\C + CD\cd <--> cd
C\cd <--> cd
D\C + cd <--> CD\cd

---------------------------
have everything in A
b subset B, match with B\b
bad when B\b in A
b --- B\b -- A\(B\b)
               v complement in B cap A, ie. universe(b) and universe(A\(B\b))
b\A + B\b --- (AB)\(B\b) -- A\((AB)\(B\b))

~~~~~~~

11010 , 10110, 10001
A   = 11010
B   = 10110
C   = 01001
AB  = 10010
ABC = 00000

current (A):
00000 --- 11010
10000 --- 01010
01000 --- 10010
00010 --- 11000

[A -> A+B]

ADD: 00000 --- 10110
bad: 00000 --- 11010 (in A)
intersection: AB, fix with: 10010
mat: 00000 ~~~ 10010 (in AB)
mat: orig(00000), new(10010): 11010 ~~~ 00100 (~10110 in AB or B\A)
mat: orig(10010), new(00000): 01000 ~~~ 10110 (~11010 in AB or A\B)

ADD: 10000 --- 00110
bad: 10000 --- 01010
intersection: AB, fix with: 00010
mat: 10000 ~~~ 00010
mat: orig(10000), new(00010): 01010 ~~~ 10100
mat: orig(00010), new(10000): 11000 ~~~ 00110

current (A+B):
00000 --- 10010
10000 --- 00010
01000 --- 10110
00100 --- 11010
11000 --- 00110
10100 --- 01010

[A+B -> A+B+C]
ADD: 00000 --- 01001
bad: 00000 --- 10010 (in AB)
intersection: ABC, fix with: 00000 (kurwa)
mat: 00000 ~~~ 00000 ??? don't do this! kurwa
mat: orig(00000), new(00000): 10001 ~~~ 01001 (~10010 in ABC)

ADD: 01000 --- 00001
bad: 01000 --- 10110 (in A+B)
intersection: (A+B)C, fix with: 00000 (kurwa)
mat: 01000 ~~~ 00000 (yes)
mat: orig(01000), new(00000): 10110 ~~~ 10010
mat: orig(00000), new(01000): 10010 ~~~ 00001 (kurwa)


A   = 11010
B   = 10110
C   = 01001
AB  = 10010
ABC = 00000

*/
