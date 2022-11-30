#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/two_sat.h"

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
  static constexpr int m = 7;
  vector<int> d(m);
  for(int i=0; i<m; i++) {
    cin >> d[i];
  }
  vector g(n, vector<int>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
    }
  }
  int x, y;
  cin >> x >> y;

  vector<int> s(1, 0);
  partial_sum(begin(d), end(d), back_inserter(s));
  assert(size(s) == 8);
  two_sat sat(s.back());

  auto get = [&](int day, int v) {
    return 2 * (s[day - 1] + abs(v) - 1) + (v < 0);
  };

  sat.add_edge(get(6, x) ^ 1, get(6, x));
  sat.add_edge(get(7, y) ^ 1, get(7, y));

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      for(int k=0; k<j; k++) {
        // either j or k is wrong
        sat.or_clause(get(j+1, g[i][j]) ^ 1, get(k+1, g[i][k]) ^ 1);
      }
    }
  }

  if(sat.solve()) {
    cout << "possible" << nl;
  } else {
    cout << "impossible" << nl;
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
