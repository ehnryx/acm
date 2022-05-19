#include <bits/stdc++.h>
using namespace std;

%:include "data_structure/circular_buffer.h"
%:include "graph/graph.h"

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

  int n;
  cin >> n;
  graph_list<int> graph(n+1);
  vector<int> have(n+1);
  for(int i=1; i<=n; i++) {
    int need, m;
    cin >> need >> m;
    for(int j=0; j<m; j++) {
      int from, w;
      cin >> from >> w;
      graph.add_edge(from, i, w);
      have[i] += w;
    }
    have[i] -= need;
  }

  int ans = n;

  circular_buffer<int> bfs(n);
  bfs.push_front(1);
  have[1] = -1;
  while(!empty(bfs)) {
    int u = bfs.back();
    bfs.pop_back();
    ans--;
    for(auto [v, c] : graph[u]) {
      if(have[v] < 0) continue;
      have[v] -= c;
      if(have[v] < 0) {
        bfs.push_front(v);
      }
    }
  }

  cout << ans << nl;

  return 0;
}
