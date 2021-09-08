#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/tree/lca_binary_jumping.h"
#include "../../../lca/tree/compressed_tree.h"

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

tuple<ll, map<int, int>, int> solve(const compressed_tree& tree, int u, int want) {
  ll res = 0;
  map<int, int> dists;
  if (tree.given[u]) dists[0] = 1;
  int offset = 0;
  for (auto [v, c] : tree[u]) {
    auto [add, subdists, suboff] = solve(tree, v, want);
    res += add;
    suboff += c;
    if (size(dists) < size(subdists)) {
      swap(dists, subdists);
      swap(offset, suboff);
    }
    for (auto [d, cnt] : subdists) {
      int actual = d + suboff; // actual distance
      // try to find actual + X + offset == want in dists
      if (dists.count(want - actual - offset)) {
        res += (ll)dists[want - actual - offset] * cnt;
      }
    }
    for (auto [d, cnt] : subdists) {
      dists[d + suboff - offset] += cnt;
    }
  }
  return tuple(res, move(dists), offset);
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

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1);
    for(int i=1; i<n; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    lca_binary_jumping tree(move(adj), 1);

    while(m--) {
      int k, d;
      cin >> k >> d;
      vector<int> verts(k);
      for(int i=0; i<k; i++) {
        cin >> verts[i];
      }
      compressed_tree graph(tree, verts);
      cout << get<0>(solve(graph, 0, d)) << nl;
    }
  }

  return 0;
}

/*
 * given S, want to count number of i<j such that d(i,j) = D
 * d(i,j) = depth(i) + depth(j) - 2*depth(lca(i,j)) = D
 * compress tree, then count at lca
 */
