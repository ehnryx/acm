#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/breadth_first.h"

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

  auto idx = [n, m](int i, int j) -> int {
    return i*m + j;
  };

  vector grid(n, vector<char>(m));
  vector_graph<void> g(n*m);
  int source = -1, sink = -1;
  vector<int> water_sources;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> grid[i][j];
      if(grid[i][j] == 'S') {
        source = idx(i, j);
      } else if(grid[i][j] == 'D') {
        sink = idx(i, j);
      } else if(grid[i][j] == '*') {
        water_sources.push_back(idx(i, j));
      }
      if(grid[i][j] != 'X') {
        if(i and grid[i-1][j] != 'X') {
          g.add_edge(idx(i, j), idx(i-1, j));
        }
        if(j and grid[i][j-1] != 'X') {
          g.add_edge(idx(i, j), idx(i, j-1));
        }
      }
    }
  }
  assert(source != -1 and sink != -1);

  auto water = breadth_first(g)
    .run_edge_func(
      water_sources,
      [sink](int, int, int v, int dv) {
        return dv == -1 and v != sink;
      });
  assert(water.dist[sink] == -1);

  auto ans = breadth_first(g)
    .run_edge_func(
      source,
      [&water](int, int du, int v, int dv) {
        return dv == -1 and (du + 1) < unsigned(water.dist[v]);
      })
    .dist[sink];

  if(ans == -1) {
    cout << "KAKTUS" << nl;
  } else {
    cout << ans << nl;
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
