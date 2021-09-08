#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/graph/min_cost_flow.h"

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

  int n;
  cin >> n;
  vector<pt> a, b;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    a.emplace_back(x, y);
  }
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    b.emplace_back(x, y);
  }

  min_cost_flow<int, ld, false> flow(2*n + 2);
  const int source = 2*n;
  const int sink = 2*n + 1;
  for(int i=0; i<n; i++) {
    flow.add_edge(source, i, 1, 0);
    flow.add_edge(i+n, sink, 1, 0);
    for(int j=0; j<n; j++) {
      flow.add_edge(i, j+n, 1, abs(a[i] - b[j]));
    }
  }
  auto [f, cost] = flow.flow(source, sink);
  assert(f == n);

  for(int i=0; i<n; i++) {
    for(auto e : flow.adj[i]) {
      if(e.flow > 0) {
        cout << i + 1 << " " << e.to - n + 1 << nl;
      }
    }
  }

  return 0;
}
