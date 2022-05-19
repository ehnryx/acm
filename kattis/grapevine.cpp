#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"

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

  int n, m, maxd;
  cin >> n >> m >> maxd;
  unordered_map<string, int> remap;
  vector<int> sk(n);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    remap[s] = i;
    cin >> sk[i];
  }
  vector<vector<int>> adj(n);
  for(int i=0; i<m; i++) {
    string s, t;
    cin >> s >> t;
    adj[remap[s]].push_back(remap[t]);
    adj[remap[t]].push_back(remap[s]);
  }
  string source;
  cin >> source;

  queue<int> bfs;
  bfs.push(remap[source]);
  vector<bool> vis(n);
  vector<int> dist(n, -1);
  vis[remap[source]] = true;
  dist[remap[source]] = 0;
  int ans = 0;
  while(!empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      if(!vis[v]) {
        ans += (dist[v] == -1 && dist[u] + 1 <= maxd);
        dist[v] = max(dist[v], dist[u] + 1);
        if(--sk[v] == 0) {
          vis[v] = true;
          bfs.push(v);
        }
      }
    }
  }

  cout << ans << nl;

  return 0;
}
