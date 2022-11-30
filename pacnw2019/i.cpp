#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/dinic.h"

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

  int n;
  cin >> n;

  vector<string> s(n);
  vector<vector<int>> adj(n);
  for(int i=0; i<n; i++) {
    cin >> s[i];
    for(int j=0; j<i; j++) {
      bool ok = false;
      string t = s[j];
      for(int ii=0; ii<size(s[j]); ii++) {
        for(int jj=0; jj<ii; jj++) {
          swap(t[ii], t[jj]);
          ok |= (t == s[i]);
          swap(t[ii], t[jj]);
        }
      }
      if(ok) {
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    }
  }

  vector<int> dist(n, -1);
  for(int i=0; i<n; i++) {
    if(dist[i] != -1) continue;
    queue<int> bfs;
    dist[i] = 0;
    bfs.push(i);
    while(!empty(bfs)) {
      int u = bfs.front();
      bfs.pop();
      for(int v : adj[u]) {
        if(dist[v] != -1) continue;
        dist[v] = dist[u] ^ 1;
        bfs.push(v);
      }
    }
  }

  dinic<int> graph(n + 2);
  const int source = n;
  const int sink = n + 1;
  for(int i=0; i<n; i++) {
    for(int j : adj[i]) {
      if(dist[i]) {
        graph.add_edge(i, j);
      }
    }
    if(dist[i]) {
      graph.add_edge(source, i);
    } else {
      graph.add_edge(i, sink);
    }
  }
  int flow = graph.flow(source, sink);

  cout << n - flow << nl;

  return 0;
}
