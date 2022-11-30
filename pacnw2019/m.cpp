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


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  vector g(n+2, vector<char>(m+2));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
    }
  }

  auto get = [n, m](int i, int j, int dir) -> int {
    return 4 * ((i-1)*m + (j-1)) + dir;
  };
  const int out = n*m * 4;

  vector<int> dsu(out + 1, -1);
  function<int(int)> find = [&](int i) -> int {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  auto link = [&](int i, int j) -> void {
    if(find(i) == find(j)) return;
    dsu[find(i)] = find(j);
  };

  vector<pair<int, int>> edges;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] == '.') {
        for(int t=1; t<4; t++) {
          link(get(i, j, 0), get(i, j, t));
        }
      } else if(g[i][j] == '/') {
        link(get(i, j, 0), get(i, j, 1));
        link(get(i, j, 2), get(i, j, 3));
        edges.emplace_back(get(i, j, 0), get(i, j, 2));
      } else {
        link(get(i, j, 0), get(i, j, 2));
        link(get(i, j, 1), get(i, j, 3));
        edges.emplace_back(get(i, j, 0), get(i, j, 1));
      }
      if(i == 1) link(get(i, j, 0), out);
      if(i == n) link(get(i, j, 3), out);
      if(j == 1) link(get(i, j, 1), out);
      if(j == m) link(get(i, j, 2), out);
      if(1 < i) link(get(i, j, 0), get(i-1, j, 3));
      if(1 < j) link(get(i, j, 1), get(i, j-1, 2));
    }
  }

  int ans = 0;
  for(auto [a, b] : edges) {
    if(find(a) != find(b)) {
      link(a, b);
      ans++;
    }
  }
  cout << ans << nl;

  return 0;
}
