#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

const long long INF = 0x3f3f3f3f3f3f3f3f;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, m, f, s, t;
  cin >> n >> m >> f >> s >> t;

  vector<vector<pair<int,int>>> adj(2*n);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
    adj[a + n].emplace_back(b + n, c);
    adj[b + n].emplace_back(a + n, c);
  }
  for(int i=0; i<f; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].emplace_back(b + n, 0);
  }
  for(int i=0; i<n; i++) {
    adj[i].emplace_back(i + n, 0);
  }

  struct Item {
    int u;
    long long d;
    Item(int _u, long long _d): u(_u), d(_d) {}
    bool operator < (const Item& o) const {
      return d > o.d;
    }
  };

  vector<long long> dist(2*n, INF);
  vector<bool> vis(2*n);
  priority_queue<Item> dijk;
  dijk.emplace(s, 0);
  dist[s] = 0;
  while(!dijk.empty()) {
    auto [u, d] = dijk.top();
    dijk.pop();
    if(vis[u]) continue;
    vis[u] = true;
    for(auto [v, c] : adj[u]) {
      if(d + c < dist[v]) {
        dist[v] = d + c;
        dijk.emplace(v, d + c);
      }
    }
  }
  cout << dist[t + n] << nl;

  return 0;
}
