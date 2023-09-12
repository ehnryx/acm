#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/dijkstra.h"
%:include "ds/union_find.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  union_find dsu(n+1);
  vector<pair<int, int>> to(n+1);
  graph_t<ll> graph(n+1);
  for(int i=1; i<=n; i++) {
    int b, c;
    cin >> b >> c;
    to[i] = pair(b, c);
    graph.add_edge(i, b, c);
    dsu.link(i, b);
  }

  vector<ll> topdist(n+1), cyclen(n+1);
  vector<bool> vis(n+1);
  for(int i=1; i<=n; i++) {
    if(dsu[i] != i) continue;
    vis[i] = true;
    vector<int> path = { i };
    int u = to[i].first;
    while(not vis[u]) {
      vis[u] = true;
      path.push_back(u);
      u = to[u].first;
    }

    vector<int> cycle = { u };
    while(path.back() != u) {
      cycle.push_back(path.back());
      path.pop_back();
    }
    reverse(begin(cycle), end(cycle));

    ll offset = 0;
    for(int v : cycle) {
      topdist[v] = offset;
      offset += to[v].second;
    }
    for(int v : cycle) {
      cyclen[v] = offset;
    }
  }

  vector<vector<pair<int, int>>> adj(n+1);
  for(int i=1; i<=n; i++) {
    if(cyclen[i]) continue;
    adj[to[i].first].emplace_back(i, to[i].second);
  }

  static constexpr int L = 17;
  vector<array<pair<int, ll>, L>> anc(n+1);
  vector<int> depth(n+1);
  auto build = [&](auto&& self, int u, int d=0) -> void {
    assert(anc[u][0] == pair(0, 0ll));
    anc[u][0] = cyclen[u] ? pair(0, 0) : to[u];
    depth[u] = d;
    for(int j=1; j<L; j++) {
      assert(anc[u][j] == pair(0, 0ll));
      int mid = anc[u][j-1].first;
      anc[u][j] = pair(anc[mid][j-1].first, anc[u][j-1].second + anc[mid][j-1].second);
    }
    for(auto [v, c] : adj[u]) {
      self(self, v, d+1);
    }
  };
  for(int i=1; i<=n; i++) {
    if(cyclen[i]) {
      build(build, i);
    }
  }

  auto get_root = [&](int u) -> pair<int, ll> {
    ll res = 0;
    for(int j=L-1; j>=0; j--) {
      if(anc[u][j].first) {
        res += anc[u][j].second;
        u = anc[u][j].first;
      }
    }
    return pair(u, res);
  };

  auto lca = [&](int u, int v) -> ll {
    if(depth[u] < depth[v]) swap(u, v);
    ll res = 0;
    for(int j=L-1; j>=0; j--) {
      if(depth[u] - (1<<j) >= depth[v]) {
        res += anc[u][j].second;
        u = anc[u][j].first;
      }
    }
    if(u == v) return res;
    for(int j=L-1; j>=0; j--) {
      if(anc[u][j].first != anc[v][j].first) {
        res += anc[u][j].second + anc[v][j].second;
        u = anc[u][j].first;
        v = anc[v][j].first;
      }
    }
    assert(u != v and anc[u][0].first == anc[v][0].first);
    return res + anc[u][0].second + anc[v][0].second;
  };

  auto cyc_dist = [&](int u, int v) -> ll {
    if(topdist[u] < topdist[v]) swap(u, v);
    return min(topdist[u] - topdist[v], topdist[v] - topdist[u] + cyclen[u]);
  };

  int n_extra;
  cin >> n_extra;
  vector<int> all;
  for(int i=0; i<n_extra; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph.add_edge(a, b, c);
    all.push_back(a);
    all.push_back(b);
  }
  sort(begin(all), end(all));
  all.resize(unique(begin(all), end(all)) - begin(all));
  vector<dijkstra<ll>> bfs;
  bfs.reserve(size(all));
  for(int s : all) {
    bfs.emplace_back(dijkstra<ll>(graph, -1).run(s));
  }

  int q;
  cin >> q;
  while(q--) {
    int s, t;
    cin >> s >> t;
    uint64_t ans = -1;
    if(dsu[s] == dsu[t]) {
      auto [rs, ds] = get_root(s);
      auto [rt, dt] = get_root(t);
      if(rs == rt) {
        ans = min(ans, uint64_t(lca(s, t)));
      } else {
        ans = min(ans, uint64_t(ds + dt + cyc_dist(rs, rt)));
      }
    }
    for(auto& it : bfs) {
      if(it.dist[s] != -1 and it.dist[t] != -1) {
        ans = min(ans, uint64_t(it.dist[s] + it.dist[t]));
      }
    }
    cout << int64_t(ans) << nl;
  }
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
