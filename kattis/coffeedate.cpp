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

  int n, m, s, t;
  cin >> n >> m >> s >> t;
  vector<vector<tuple<int,int,int,int>>> adj(n);
  for(int i=0; i<m; i++) {
    int c, k;
    cin >> c >> k;
    vector<int> stops(k);
    for(int j=0; j<k; j++) {
      cin >> stops[j];
    }
    for(int j=1, sum=0; j<k; j++) {
      int d;
      cin >> d;
      adj[stops[j-1]].emplace_back(stops[j], d, sum, c);
      sum += d;
    }
  }

  struct Item {
    int u, d;
    bool operator < (const Item& o) const {
      return d > o.d;
    }
  };

  function<vector<int>(int)> dijkstra = [=](int source) {
    priority_queue<Item> dijk;
    dijk.push({source, 0});
    vector<int> dist(n, -1);
    while(!dijk.empty()) {
      auto [u, d] = dijk.top();
      dijk.pop();
      if(dist[u] != -1) continue;
      dist[u] = d;
      for(auto [v, c, start, period] : adj[u]) {
        if(dist[v] != -1) continue;
        int add = (period - (d - start) % period) % period;
        dijk.push({v, d + add + c});
      }
    }
    return dist;
  };

  auto from = dijkstra(s);
  auto to = dijkstra(t);
  int ans = -1;
  for(int i=0; i<n; i++) {
    if(from[i] == -1 || to[i] == -1) continue;
    int cur = max(from[i], to[i]);
    if(ans == -1 || cur < ans) {
      ans = cur;
    }
  }
  if(ans == -1) {
    cout << "NO COFFEE FOR YOU" << nl;
  } else {
    cout << ans << nl;
  }

  return 0;
}
