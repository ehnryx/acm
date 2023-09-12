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
  int s, t, n;
  cin >> s >> t >> n;
  vector<pair<int, int>> ev;
  for(int i=0; i<n; i++) {
    int m, h;
    cin >> m >> h;
    m = min(m, s);
    ev.emplace_back(m, h);
  }
  ev.emplace_back(t, 0);
  sort(begin(ev), end(ev), greater<>());
  if(ev.front().first < s) {
    return void(cout << -1 << nl);
  }

  int best = numeric_limits<int>::max();
  ld loghave = log((ld)s);
  ld logvi = 1; //numeric_limits<ld>::infinity();
  ld ans = 0;
  for(auto [m, h] : ev) {
    if(h < best) {
      auto logcur = log((ld)m);
      ans += (logcur - loghave) / logvi;
      if(m == t) break;
      logvi = -log((ld)2) / h;
      loghave = logcur;
      best = h;
    }
  }
  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << setprecision(10);
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
