#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "misc/mo_solver.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  mo_solver<int> solver(1, n);
  for(int i=0; i<m; i++) {
    int l, r;
    cin >> l >> r;
    solver.add_event(l, r, i);
  }
  vector<ll> ans(m);

  vector<int> cnt(*max_element(begin(a), end(a)) + 1);

  ll total = 0;
  solver.solve(
      [&](int i, int v, int) {
        total -= (ll)cnt[a[i]] * cnt[a[i]] * a[i];
        cnt[a[i]] += v;
        total += (ll)cnt[a[i]] * cnt[a[i]] * a[i]; },
      [&](int i) { ans[i] = total; });

  for(auto v : ans) {
    cout << v << nl;
  }
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
