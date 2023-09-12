#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/dinic.h"
%:include "ds/union_find.h"

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
  vector g(n+2, vector(m+2, 'W'));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
    }
  }

  auto get = [m](int i, int j) {
    return (i-1)*m + (j-1);
  };

  dinic<int> graph(n*m + 2);
  const int source = n*m;
  const int sink = source + 1;
  int ans = 0;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] != 'C') continue;
      const auto nbs = {
        pair(i+1, j), pair(i, j+1),
        pair(i-1, j), pair(i, j-1),
      };
      bool ok = true;
      for(auto [ni, nj] : nbs) {
        ok &= (g[ni][nj] != 'L');
      }
      if(not ok) {
        g[i][j] = 'W';
        continue;
      }
      ans++;
      if((i+j) % 2) {
        graph.add_edge(source, get(i, j));
        for(auto [ni, nj] : nbs) {
          if(g[ni][nj] == 'C') {
            graph.add_edge(get(i, j), get(ni, nj));
          }
        }
      } else {
        graph.add_edge(get(i, j), sink);
      }
    }
  }
  ans -= graph.flow(source, sink);

  union_find dsu(n*m);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] != 'L') continue;
      const auto nbs = {
        pair(i+1, j), pair(i, j+1),
        pair(i-1, j), pair(i, j-1),
      };
      for(auto [ni, nj] : nbs) {
        if(g[ni][nj] == 'L') {
          dsu.link(get(i, j), get(ni, nj));
        }
      }
    }
  }
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] == 'L' and dsu[get(i, j)] == get(i, j)) {
        ans++;
      }
    }
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
