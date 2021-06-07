#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

ll solve(ll n) {
  if (n == 1) return 1;
  int k = 0;
  while (1LL << (k + 1) < n) {
    k++;
  }
  assert(1LL << k < n);
  if (1LL << (k + 1) == n) {
    return 3 * solve(1LL << k);
  } else {
    return solve(1LL << k) + 2 * solve(n - (1LL << k));
  }
}

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  ll n = 1'000'000'000'000;
  if (argc > 1) n = atoll(argv[1]);
  cout << solve((n + 3) / 4) << nl;

  return 0;
}
