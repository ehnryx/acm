#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  vector g(n+1, vector<int>(n+1));
  vector<vector<pair<int, int>>> ev(m+1);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cin >> g[i][j];
      ev[g[i][j]].emplace_back(i, j);
    }
  }

  vector<ll> rows(n+1), cols(n+1);
  ll big = numeric_limits<ll>::max();
  for(int value=1; value<=m; value++) {
    vector<ll> nrows(n+1, big), ncols(n+1, big);
    for(auto [a, b] : ev[value]) {
      ll cur = big;
      for(int i=1; i<=n; i++) {
        if(rows[i] != big) {
          cur = min(cur, rows[i] + (a-i)*(a-i));
        }
        if(cols[i] != big) {
          cur = min(cur, cols[i] + (b-i)*(b-i));
        }
      }
      nrows[a] = min(nrows[a], cur);
      ncols[b] = min(ncols[b], cur);
    }
    rows = move(nrows);
    cols = move(ncols);
  }

  ll ans = min(
      *min_element(begin(rows), end(rows)),
      *min_element(begin(cols), end(cols)));
  cout << (ans == big ? -1 : ans) << nl;

  return 0;
}
