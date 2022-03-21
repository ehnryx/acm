#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 9;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m, k;
  cin >> n >> m >> k;
  vector<pair<int, int>> edges;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    edges.emplace_back(a-1, b-1);
  }

  vector<Int> kpow(n+1);
  kpow[0] = 1;
  for(int i=1; i<=n; i++) {
    kpow[i] = kpow[i-1] * k;
  }

  vector ncr(m+1, vector<Int>(m+1));
  for(int i=0; i<=m; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  vector<Int> cnt(m+2);
  for(int bm=0; bm<1<<m; bm++) {
    vector<int> dsu(n, -1);
    function<int(int)> find = [&](int i) {
      if(dsu[i] == -1) return i;
      return dsu[i] = find(dsu[i]);
    };
    function<bool(int, int)> link = [&](int i, int j) {
      i = find(i);
      j = find(j);
      if(i == j) return false;
      dsu[i] = j;
      return true;
    };

    int groups = n;
    for(int i=0; i<m; i++) {
      if(!(bm >> i & 1)) continue;
      groups -= link(edges[i].first, edges[i].second);
    }

    cnt[__builtin_popcount(bm)] += kpow[groups];
  }

  Int total = kpow[n];
  for(int i=0; i<=m; i++) {
    Int ans = 0;
    vector<Int> num(m+2);
    for(int j=i+1; j<=m; j++) {
      Int mul = -num[j] + 1;
      for(int t=j; t<=m; t++) {
        num[t] += mul * ncr[t][j];
      }
      ans += mul * cnt[j];
    }
    cout << total - ans << " ";
    total = ans;
  }
  cout << nl;

  return 0;
}
