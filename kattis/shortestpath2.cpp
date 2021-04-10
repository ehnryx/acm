#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Item {
  int u, d;
  Item(int _u, int _d): u(_u), d(_d) {}
  bool operator < (const Item& o) const {
    return d > o.d;
  }
};

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

  for(int n, m, q, s; cin >> n >> m >> q >> s && n; ) {
    vector<vector<tuple<int,int,int,int>>> adj(n);
    for(int i=0; i<m; i++) {
      int u, v, t0, p, d;
      cin >> u >> v >> t0 >> p >> d;
      adj[u].emplace_back(v, t0, p, d);
    }

    vector<int> dist(n, -1);
    priority_queue<Item> dijk;
    dijk.emplace(s, 0);
    while(!dijk.empty()) {
      auto [u, d] = dijk.top();
      dijk.pop();
      if(dist[u] != -1) continue;
      dist[u] = d;
      for(auto [v, t0, p, c] : adj[u]) {
        if(dist[v] != -1) continue;
        if(p > 0) {
          int cur = max(d, t0);
          int add = (p - (cur - t0) % p) % p;
          dijk.emplace(v, cur + add + c);
        } else if(d <= t0) {
          dijk.emplace(v, t0 + c);
        }
      }
    }

    for(int i=0; i<q; i++) {
      int u;
      cin >> u;
      if(dist[u] < 0) {
        cout << "Impossible" << nl;
      } else {
        cout << dist[u] << nl;
      }
    }
    cout << nl;
  }

  return 0;
}
