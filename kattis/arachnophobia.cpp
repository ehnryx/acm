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

  int n, m, T;
  cin >> n >> m >> T;
  vector<vector<pair<int,int>>> adj(n + 1);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }
  int s, t;
  cin >> s >> t;
  int k;
  cin >> k;
  for(int i=0; i<k; i++) {
    int v;
    cin >> v;
    adj[n].emplace_back(v, 0);
  }

  struct Item {
    int v, d;
    bool operator < (const Item& o) const {
      return d > o.d;
    }
  };
  vector<bool> bad(n + 1);
  function<vector<int>(int)> dijkstra = [&](int r) {
    vector<int> dist(n + 1, INF);
    priority_queue<Item> dijk;
    dijk.push({r, 0});
    while(!dijk.empty()) {
      auto [u, d] = dijk.top();
      dijk.pop();
      if(dist[u] < INF) continue;
      dist[u] = d;
      for(auto [v, c] : adj[u]) {
        if(dist[v] < INF || bad[v]) continue;
        dijk.push({v, c + d});
      }
    }
    return dist;
  };
  vector<int> spider = dijkstra(n);

  int l = 0;
  int r = spider[s];
  while(l < r) {
    int d = (l + r + 1) / 2;
    for(int i=0; i<n; i++) {
      bad[i] = spider[i] < d;
    }
    if(dijkstra(s)[t] <= T) {
      l = d;
    } else {
      r = d-1;
    }
  }
  cout << r << nl;

  return 0;
}
