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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  vector<vector<int>> in(n), out(n);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    out[a].push_back(i);
    in[b].push_back(i);
  }

  dinic<int> g(2*m + 2);
  const int source = 2*m;
  const int sink = source + 1;
  for(int i=0; i<m; i++) {
    g.add_edge(source, i);
    g.add_edge(i + m, sink);
  }

  for(int s=0; s<n; s++) {
    vector<bool> vis(n);
    queue<int> bfs;
    bfs.push(s);
    vis[s] = true;
    while(not empty(bfs)) {
      int u = bfs.front();
      bfs.pop();
      for(int a : in[s]) {
        for(int b : out[u]) {
          g.add_edge(a, b + m);
        }
      }
      for(int v : adj[u]) {
        if(not vis[v]) {
          vis[v] = true;
          bfs.push(v);
        }
      }
    }
  }

  cout << m - g.flow(source, sink) << nl;
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
