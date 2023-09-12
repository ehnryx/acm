#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/union_find.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m, k;
  cin >> n >> m >> k;
  vector g(n+2, vector(m+2, '.'));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
    }
  }

  struct pt {
    int i, j;
  };
  auto get = [m](pt v) {
    return (v.i - 1) * m + (v.j - 1);
  };

  vector<pair<pt, pt>> edges;
  int cnt = 0;
  for(int i=1; i<=n; i++) {
    pt last = {-1, -1};
    for(int j=1; j<=m; j++) {
      if(g[i][j] == '*') {
        cnt++;
        if(last.j != -1) {
          edges.emplace_back(last, pt{i, j});
        }
        last = {i, j};
      }
    }
  }
  for(int j=1; j<=m; j++) {
    pt last = {-1, -1};
    for(int i=1; i<=n; i++) {
      if(g[i][j] == '*') {
        if(last.i != -1) {
          edges.emplace_back(last, pt{i, j});
        }
        last = {i, j};
      }
    }
  }

  union_find dsu(n*m);

  vector out(n+2, vector(m+2, 0));
  for(auto [a, b] : edges) {
    if(cnt == k) break;
    if(dsu.link(get(a), get(b))) {
      cnt--;
      for(int i = min(a.i, b.i) + 1; i < max(a.i, b.i); i++) {
        out[i][a.j] |= 0b01;
      }
      for(int j = min(a.j, b.j) + 1; j < max(a.j, b.j); j++) {
        out[a.i][j] |= 0b10;
      }
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] == '*') {
        cout << g[i][j];
      } else if(out[i][j] == 0b10) {
        cout << '-';
      } else if(out[i][j] == 0b01) {
        cout << '|';
      } else if(out[i][j]) {
        cout << '+';
      } else {
        cout << ' ';
      }
    }
    cout << nl;
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
