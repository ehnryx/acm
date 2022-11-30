#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/breadth_first.h"
%:include "graph/depth_first.h"

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
  vector_graph<void> g(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  breadth_first bfs(g);
  depth_first dfs(g);
  int a = 0, b = 0;
  for(int i=1; i<=n; i++) {
    if(bfs.dist[i] == -1) {
      bfs.run(i);
      a++;
    }
    if(dfs.parent[i] == -1) {
      dfs.run(i);
      b++;
    }
  }
  assert(a == b);
  int c = 0, d = 0;
  for(int i=1; i<=n; i++) {
    c += (bfs.parent[i] == i);
    d += (dfs.parent[i] == i);
  }
  assert(c == d);
  assert(a == c);
  cout << (a == 1 ? "YES" : "NO") << nl;
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
