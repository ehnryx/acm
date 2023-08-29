#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "misc/mo_solver.h"
%:include "ds/fenwick_tree.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

constexpr int M = 1e5 + 1;

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> pts;
  pts.reserve(n);
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    pts.emplace_back(a, b);
  }
  sort(begin(pts), end(pts));

  mo_solver<int, int> solver(0, M-1);
  for(int i=0; i<m; i++) {
    int l, r, b, t;
    cin >> l >> r >> b >> t;
    l = lower_bound(begin(pts), end(pts), pair(l, 0)) - begin(pts);
    r = upper_bound(begin(pts), end(pts), pair(r, M)) - begin(pts);
    if(l < r) {
      solver.add_event(l, r-1, b, t);
    }
  }

  ll ans = 0;
  fenwick_tree<int> st(M);
  solver.solve(
    [&](int i, int v, ...) {
      st.update_point(pts[i].second, v);
    },
    [&](int l, int r) {
      ans += st.query_range(l, r);
    }
  );
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
