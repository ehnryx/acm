#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


/**
P = original permutation

f[n][s] = length of list after [1..n] expanded s steps
f[n][0] = n
f[n][s] = sum_1_n f[i][s-1]

Need in constant time:
g(n, s, k) = number of occurrences of k after [1..n] expanded s steps

PSeg[s].query(ver=n, 0, i) = for P.restrict[1..n] expanded s steps, length of list of the first i groups

Given query to count k in the prefix of length a

*/

int main() {
  return 0;
}