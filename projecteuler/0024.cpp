#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  ll n = 1'000'000;
  if (argc > 1) n = atoll(argv[1]);

  vector<int> v(10);
  iota(begin(v), end(v), 0);
  for(int i=1; i<n; i++) {
    next_permutation(begin(v), end(v));
  }

  for(int i : v) {
    cout << i;
  } cout << nl;

  return 0;
}
