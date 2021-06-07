#include <bits/stdc++.h>
using namespace std;

#ifdef HENRYX
#include "../../lca/graph/dinic.h"
#include "../../lca/graph/flow_with_demands.h"
#include "../../lca/graph/euler_trail.h"
#else
#include "dinic.h"
#include "flow_with_demands.h"
#include "euler_trail.h"
#endif

constexpr char nl = '\n';

const int L = 64;

int in(int i, int j) {
  return 2 * (i*L + j);
}

int out(int i, int j) {
  return 2 * (i*L + j) + 1;
}

void solve(int n) {
  bool ok = true;
  map<pair<int,int>,int> cnt;
  map<int,int> remap;
  for(int i=0; i<n; i++) {
    long long v;
    cin >> v;
    if (!ok) continue;
    int twos = __builtin_ctzll(v);
    int threes = 0;
    while(v % 3 == 0) {
      v /= 3;
      threes++;
    }
    ok &= (__builtin_popcountll(v) == 1);
    cnt[pair(threes, twos)]++;
    remap[in(threes, twos)];
    remap[out(threes, twos)];
  }
  if(!ok || !cnt.count(pair(0, 0))) {
    cout << "NO" << nl;
    return;
  }

  int rid = 0;
  vector<int> order;
  for(auto& it : remap) {
    it.second = rid++;
    order.emplace_back(it.first / 2);
  }

  flow_with_demands<dinic, int> graph(rid + 1);
  graph.add_edge(rid, remap[in(0, 0)], 1, 1);
  for (const auto& [key, c] : cnt) {
    const auto& [i, j] = key;
    graph.add_edge(remap[in(i, j)], remap[out(i, j)], c, c);
    if(remap.count(in(i, j-1))) {
      graph.add_edge(remap[out(i, j)], remap[in(i, j-1)], 0, n);
    }
    if(remap.count(in(i, j+1))) {
      graph.add_edge(remap[out(i, j)], remap[in(i, j+1)], 0, n);
    }
    if(remap.count(in(i+1, j))) {
      graph.add_edge(remap[out(i, j)], remap[in(i+1, j)], 0, 1);
    }
    graph.add_edge(remap[out(i, j)], rid, 0, 1);
  }

  if(graph.flowable()) {
    vector<vector<pair<int,int>>> adj(rid/2);
    int num_edges = 0;
    for(const auto& [key, _] : cnt) {
      int u = remap[out(key.first, key.second)];
      for (const auto& e : graph.adj[u]) {
        if (e.to >= rid) continue;
        for (int k = 0; k < e.flow; k++) {
          adj[u/2].emplace_back(e.to/2, -1);
          num_edges++;
        }
      }
    }
    vector<int> trail = euler_trail(adj, num_edges, 0);
    //assert(!trail.empty());
    if (trail.empty()) {
      cout << "NO" << nl;
    } else {
      cout << "YES" << nl;
      for(int v : trail) {
        int i = order[2*v] / L, j = order[2*v] % L;
        cout << (llround(powl(3, i)) << j) << " ";
      }
      cout << nl;
    }
  } else {
    cout << "NO" << nl;
  }
}

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

  for(int n; cin >> n && n; ) {
    solve(n);
  }

  return 0;
}
