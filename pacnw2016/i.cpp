#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll solve(vector<pair<int, int>> ev, int k) {
  sort(begin(ev), end(ev), greater<>());
  ll ans = 0;
  int have = 0;
  for(auto [x, m] : ev) {
    int sub = min(have, m);
    have -= sub;
    m -= sub;
    if(m > 0) {
      ans += m/k * (ll)x;
      m %= k;
      if(m > 0) {
        ans += x;
        have = k - m % k;
      }
    }
  }
  return ans;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, k;
  cin >> n >> k;
  vector<pair<int, int>> left, right;
  for(int i=0; i<n; i++) {
    int x, m;
    cin >> x >> m;
    if(x < 0) {
      left.emplace_back(-x, m);
    } else if(x > 0) {
      right.emplace_back(x, m);
    }
  }
  cout << 2 * (solve(left, k) + solve(right, k)) << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
