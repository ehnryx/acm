#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

%:include "graph/graph.h"
%:include "data_structure/circular_buffer.h"

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
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m, x, y;
  cin >> n >> m >> x >> y;
  graph_list<void> g(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }

  circular_buffer<int> bfs(n);
  bfs.push_front(y);
  vector<bool> vis(n+1);
  vis[y] = true;

  vector<int> out(n+1);
  while(!empty(bfs)) {
    int u = bfs.back();
    bfs.pop_back();
    for(int v : g[u]) {
      if(vis[v]) continue;
      out[v]++;
      if(2 * out[v] >= g[v].size()) {
        vis[v] = true;
        bfs.push_front(v);
      }
    }
  }

  cout << (vis[x] ? "leave" : "stay") << nl;

  return 0;
}
