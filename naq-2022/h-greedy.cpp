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
  int n, l, r;
  cin >> n >> l >> r;
  vector<int> x(n);
  for(int i=0; i<n; i++) {
    cin >> x[i];
  }
  sort(begin(x), end(x));

  vector<int> d(n+1);
  for(int i=1; i<n; i++) {
    if(x[i] - x[i-1] < l) {
      return void(cout << -1 << nl);
    }
    d[i] = 2 * (x[i] - x[i-1] - l);
  }
  r -= l;
  d[0] = d[n] = r;

  ll ans = (ll)n * l;
  for(int i=0; i<n; i++) {
    int flow = min({r, d[i], d[i+1]});
    ans += flow;
    d[i+1] -= flow;
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
