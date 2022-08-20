#include <bits/stdc++.h>
using namespace std;

//%:include "utility/defines.h"
//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

vector<pair<int, int>> solve(int n, const vector<vector<vector<bool>>>& ds, const vector<int>& all) {
  int m = size(all);
  const int T = 42;
  for(int it=0; it < m*m * T; it++) {
    int a = all[rng() % m];
    int b = all[rng() % m];
    if (a == b) continue;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector ds(n+1, vector(n+1, vector<bool>(n+1)));
    for(int i=1; i<=n-1; i++) {
      for(int j=1; j<=n-i; j++) {
        for(int k=1; k<=n; k++) {
          char c;
          cin >> c;
          // d[i][k] ?= d[i+j][k]
          if(c == '1') {
            ds[k][i][i+j] = true;
            ds[k][i+j][i] = true;
          }
        }
      }
    }
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        ds[i][j][j] = true;
      }
    }

    vector<int> all(n);
    iota(begin(all), end(all), 1);
    vector<pair<int, int>> ans = solve(n, ds, all);
    if (empty(ans)) {
      cout << "No" << nl;
    } else {
      cout << "Yes" << nl;
      for(auto [a, b] : ans) {
        cout << a << " " << b << nl;

      }
    }
  }

  return 0;
}
