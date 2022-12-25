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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> edges;
  vector<vector<int>> adj(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    edges.emplace_back(a, b);
  }

  const int big = n + 1;
  vector dist(n+1, vector<int>(n+1, big));
  vector<vector<pair<int, int>>> others(n+1);
  for(int s=1; s<=n; s++) {
    queue<pair<int, int>> bfs;
    bfs.emplace(s, s);
    dist[s][s] = 0;
    while(not empty(bfs)) {
      auto [u, from] = bfs.front();
      bfs.pop();
      for(int v : adj[u]) {
        if(dist[s][v] == big) {
          dist[s][v] = dist[s][u] + 1;
          bfs.emplace(v, u);
        } else if(v != from and u < v) {
          others[s].emplace_back(u, v);
        }
      }
    }
  }

  int best = big;
  int cnt = 0;
  for(auto [s, t] : edges) {
    for(auto [a, b] : others[s]) {
      int len = 2 + min(dist[s][a] + dist[t][b], dist[s][b] + dist[t][a]);
      if(len < best) {
        best = len;
        cnt = 0;
      }
      cnt += (len == best);
    }
  }
  assert(cnt % best == 0);
  cout << cnt / best << nl;
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
