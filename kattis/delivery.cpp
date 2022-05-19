#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int solve(vector<pair<int, int>> v, int m) {
  sort(begin(v), end(v), greater<>());
  int ans = 0;
  int at = 0;
  for(auto [x, it] : v) {
    while(it) {
      if(at == 0) {
        at = m;
        ans += x;
      }
      int take = min(at, it);
      at -= take;
      it -= take;
    }
  }
  return 2 * ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> l, r;
  for(auto [x, v] : cin.read<pair<int, int>>(n)) {
    if(x < 0) l.emplace_back(-x, v);
    else r.emplace_back(x, v);
  }
  cout << solve(l, m) + solve(r, m) << nl;

  return 0;
}
