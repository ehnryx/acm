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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  ll n;
  int k;
  cin >> n >> k;
  vector<pair<ll, ll>> ev;
  for(int i=0; i<k; i++) {
    ll a, b;
    cin >> a >> b;
    ev.emplace_back(a, b);
    ev.emplace_back(b, -1);
  }
  sort(begin(ev), end(ev));

  map<ll, ll> dp;
  dp[0] = 0;
  for(auto [a, b] : ev) {
    if(b == -1) {
      dp[a] = max(dp[a], prev(dp.lower_bound(a))->second);
    } else {
      dp[b] = max(dp[b], prev(dp.lower_bound(a))->second + (b - a + 1));
    }
  }

  ll ans = 0;
  for(const auto& [_, v] : dp) {
    ans = max(ans, v);
  }
  cout << n - ans << nl;
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
