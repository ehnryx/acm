#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "ds/union_find.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

void solve(int n) {
  vector g(n, vector<char>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> g[i][j];
      g[i][j] -= '0';
    }
  }

  auto connect = [&](const auto& grid) -> union_find<> {
    union_find dsu(n*n);
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        if(i && grid[i][j] == grid[i-1][j]) {
          dsu.link(i + j*n, i-1 + j*n);
        }
        if(j && grid[i][j] == grid[i][j-1]) {
          dsu.link(i + j*n, i + (j-1)*n);
        }
      }
    }
    return dsu;
  };

  auto replace = [&](auto& grid, int v) -> void {
    auto dsu = connect(grid);
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        if(dsu[0] == dsu[i + j*n]) {
          grid[i][j] = v;
        }
      }
    }
  };

  auto search = [&]() -> int {
    int orig = connect(g).size(0);
    auto best = pair(orig, 0);
    for(int t=1; t<=6; t++) {
      auto ng = g;
      replace(ng, t);
      best = max(best, pair(connect(ng).size(0), -t));
    }
    return -best.second;
  };

  vector<int> cnt(6);
  while (int v = search()) {
    cnt[v-1]++;
    replace(g, v);
  }

  cout << accumulate(begin(cnt), end(cnt), 0) << nl;
  cout << cnt << nl;
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
    solve(n);
  }

  return 0;
}
