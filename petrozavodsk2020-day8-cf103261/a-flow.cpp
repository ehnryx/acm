#pragma GCC optimize("O3")
#ifdef ONLINE_JUDGE
#pragma GCC target("sse4,avx2,tune=native")
#else
#pragma GCC target("sse4,avx2")
#endif

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

const int MAGIC = 35;

// START #include "../../lca/graph/dinic.h"

template <typename T>
struct dinic {
  struct edge {
    int to, rev;
    T cap, flow;
    int idx;
    edge(int t, int r, const T& c, const T& f, int i):
      to(t), rev(r), cap(c), flow(f), idx(i) {}
  };
  vector<vector<edge>> adj;
  vector<int> layer, cur_edge;
  dinic(int n): adj(n), layer(n), cur_edge(n) {}

  void add_edge(int a, int b, const T& c, int i=0) {
    adj[a].emplace_back(b, (int)size(adj[b]),     c, 0, i);
    adj[b].emplace_back(a, (int)size(adj[a]) - 1, 0, 0, i);
  }

  bool bfs(int s, int t) {
    fill(begin(layer), end(layer), -1);
    fill(begin(cur_edge), end(cur_edge), 0);
    queue<int> todo;
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
    return layer[t] != -1 && layer[t] < MAGIC;
  }

  T dfs(int u, int t, T f) {
    if (u == t || f == 0) return f;
    T res = 0;
    for (int i = cur_edge[u]; i < (int)size(adj[u]) && f != 0; i++) {
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

  T flow(int source, int sink, int max_iters = numeric_limits<int>::max()) {
    if constexpr (!is_integral_v<T>) {
      assert(max_iters < numeric_limits<int>::max());
    }
    T inf = numeric_limits<T>::max();
    T res = 0;
    for (int i = 0; i < max_iters && bfs(source, sink); i++) {
      while (T cur_flow = dfs(source, sink, inf)) {
        res += cur_flow;
      }
    }
    return res;
  }
};

// END #include "../../lca/graph/dinic.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n1, n2, m;
  cin >> n1 >> n2 >> m;
  dinic<int> graph(n1 + n2 + 2);
  const int source = 0;
  const int sink = n1 + n2 + 1;

  for(int i=1; i<=m; i++) {
    int a, b;
    cin >> a >> b;
    graph.add_edge(a, b + n1, 1, i);
  }

  for(int i=1; i<=n1; i++) {
    graph.add_edge(source, i, 1);
  }
  for(int i=1; i<=n2; i++) {
    graph.add_edge(i + n1, sink, 1);
  }

  int flow = graph.flow(source, sink);
  cout << flow << nl;
  for(int i=1; i<=n1; i++) {
    for(const auto& e : graph.adj[i]) {
      if(e.flow > 0) {
        cout << e.idx << nl;
      }
    }
  }

  return 0;
}
