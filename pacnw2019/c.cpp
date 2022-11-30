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
  vector<vector<int>> adj(n + 1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<int> dist(n + 1, -1);
  queue<int> bfs;
  bfs.push(1);
  dist[1] = 0;
  while(!empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      if(dist[v] == -1) {
        dist[v] = dist[u] + 1;
        bfs.push(v);
      }
    }
  }
  cout << dist[n] - 1 << nl;

  return 0;
}
