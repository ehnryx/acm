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
  int n;
  cin >> n;
  vector<tuple<ll, ld, ld>> lines;
  for(int i=0; i<n; i++) {
    ll x, y;
    cin >> x >> y;
    ld m = (ld)x/y;
    ld b = -(ld)x*x/y;
    lines.emplace_back(-x, m, b);
  }
  sort(begin(lines), end(lines));

  ld ans = 1e18;
  for(int i=1; i<n; i++) {
    auto [x1, m1, b1] = lines[i-1];
    auto [x2, m2, b2] = lines[i];
    if(m1 <= m2 or x1 == x2) continue;
    ans = min(ans, (b2 - b1) / (m1 - m2));
  }
  cout << ans << nl;
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
