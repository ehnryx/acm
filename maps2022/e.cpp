#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

// START %:include "graph/dinic.h"

#include <cassert>
#include <limits>
#include <queue>
#include <vector>

template <typename T>
struct dinic {
  struct edge {
    int to, rev;
    T cap, flow;
    edge(int t, int r, const T& c, const T& f): to(t), rev(r), cap(c), flow(f) {}
  };
  std::vector<std::vector<edge>> adj;
  std::vector<int> layer, cur_edge;
  dinic(int n): adj(n), layer(n), cur_edge(n) {}

  int size() const { return (int)adj.size(); }

  void add_edge(int a, int b, const T& c = 1, bool bidirectional = false) {
    adj[a].emplace_back(b, (int)adj[b].size(), c, 0);
    adj[b].emplace_back(a, (int)adj[a].size() - 1, bidirectional ? c : 0, 0);
  }
  bool left_of_min_cut(int u) const { return layer[u] != -1; }
  void clear_flow() {
    for (std::vector<edge>& adjacency : adj) {
      for (edge& e : adjacency) {
        e.flow = 0;
      }
    }
  }

  bool bfs(int s, int t) {
    fill(begin(layer), end(layer), -1);
    fill(begin(cur_edge), end(cur_edge), 0);
    std::queue<int> todo;
    layer[s] = 0;
    todo.push(s);
    while (!empty(todo) && layer[t] == -1) {
      int u = todo.front();
      todo.pop();
      for (const edge& e : adj[u]) {
        if (layer[e.to] == -1 && e.flow < e.cap) {
          layer[e.to] = layer[u] + 1;
          todo.push(e.to);
        }
      }
    }
    return layer[t] != -1;
  }

  T dfs(int u, int t, T f) {
    if (u == t || f == 0) return f;
    T res = 0;
    for (int i = cur_edge[u]; i < (int)adj[u].size() && f != 0; i++) {
      cur_edge[u] = i; // save current edge
      if (layer[u] + 1 != layer[adj[u][i].to]) continue;
      if (T cur_flow = dfs(adj[u][i].to, t, min(f, adj[u][i].cap - adj[u][i].flow))) {
        adj[u][i].flow += cur_flow;
        adj[adj[u][i].to][adj[u][i].rev].flow -= cur_flow;
        res += cur_flow;
        f -= cur_flow;
      }
    }
    return res;
  }

  T flow(int source, int sink, int max_iters = std::numeric_limits<int>::max()) {
    if constexpr (!std::is_integral_v<T>) {
      assert(max_iters < std::numeric_limits<int>::max());
    }
    T inf = std::numeric_limits<T>::max();
    T res = 0;
    for (int i = 0; i < max_iters && bfs(source, sink); i++) {
      while (T cur_flow = dfs(source, sink, inf)) {
        res += cur_flow;
      }
    }
    return res;
  }
};

// END %:include "graph/dinic.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m, r;
  cin >> n >> m >> r;

  static constexpr int C = 200;
  dinic<int> g(n + C + 2);
  const int source = n + C;
  const int sink = n + C + 1;

  vector<string> name(n), cname;
  unordered_map<string, int> colours;
  for(int i=0, cid=0; i<n; i++) {
    cin >> name[i];
    int k;
    cin >> k;
    for(int j=0; j<k; j++) {
      string s;
      cin >> s;
      if(!colours.count(s)) {
        cname.push_back(s);
        colours[s] = cid;
        g.add_edge(n + cid, sink);
        cid++;
      }
      g.add_edge(i, n + colours[s]);
    }
  }

  int ans = -1;
  dinic<int> res(0);
  for(int bm=0; bm<1<<n; bm++) {
    if(__builtin_popcount(bm) != m) continue;
    for(int i=0; i<n; i++) {
      if(bm & 1<<i) {
        g.add_edge(source, i, r);
      }
    }
    int flow = g.flow(source, sink);
    if(flow > ans) {
      ans = flow;
      res = g;
    }
    for(int i=0; i<n; i++) {
      if(bm & 1<<i) {
        g.adj[source].clear();
        g.adj[i].pop_back();
      }
    }
    g.clear_flow();
  }

  vector<pair<int, int>> vis;
  for(auto e : res.adj[source]) {
    if(e.flow) {
      vis.emplace_back(e.to, e.flow);
    }
  }

  cout << ans << " " << size(vis) << nl;
  for(auto [s, c] : vis) {
    cout << name[s] << " " << c;
    for(auto e : res.adj[s]) {
      if(e.to != source && e.flow) {
        cout << " " << cname[e.to - n];
      }
    }
    cout << nl;
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
