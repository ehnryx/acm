#include <queue>
%:include "math/factor.h"
%:include "ds/trie.h"
#define MULTI_TEST
%:include "main.h"

vector<ll> const& divisors(ll n) {
  static map<ll, vector<ll>> memo;
  if (auto it = memo.find(n); it != memo.end()) return it->second;
  auto it = memo.emplace(n, get_divisors(n, sort_factors::Yes)).first;
  return it->second;
}

SOLVE() {
  int n;
  cin >> n;
  vector<tuple<int, int, ll>> edges;
  map<ll, vector<int>> store;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    edges.emplace_back(a - 1, b - 1, c);
    for (auto d : divisors(c)) {
      store[d].push_back(i);
    }
  }

  auto solve = [&](vector<int> const& eids) {
    vector<vector<int>> adj(n);
    for (int i : eids) {
      auto const& [a, b, _] = edges[i];
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    vector<char> vis(n);
    vector<int> dist(n, -1);
    for (int i = 0; i < n; i++) {
      if (vis[i]) continue;
      queue<int> bfs;
      vis[i] = true;
      bfs.push(i);
      int u = -1;
      while (not empty(bfs)) {
        u = bfs.front();
        bfs.pop();
        for (int v : adj[u]) {
          if (not vis[v]) {
            vis[v] = true;
            bfs.push(v);
          }
        }
      }
      assert(u != -1);
      dist[u] = 0;
      bfs.push(u);
      while (not empty(bfs)) {
        u = bfs.front();
        bfs.pop();
        for (int v : adj[u]) {
          if (dist[v] == -1) {
            dist[v] = dist[u] + 1;
            bfs.push(v);
          }
        }
      }
    }
    return *max_element(begin(dist), end(dist));
  };

  trie<int> seen;
  ll ans = 0;
  for (auto eit = rbegin(store); eit != rend(store); eit++) {
    auto const& eids = eit->second;
    if (not seen.insert(eids).second) continue;
    ans = max(ans, eit->first * solve(eids));
  }
  cout << ans << nl;
}
