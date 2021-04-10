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

  int n, m, q, k, len;
  cin >> n >> m >> q >> k >> len;
  vector<vector<pair<int,int>>> adj(n+1);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }

  struct Item {
    int u; ll d;
    Item(int _u, ll _d): u(_u), d(_d) {}
    bool operator < (const Item& o) const { return d > o.d; }
  };

  vector<ll> dist(n+1, INFLL);
  priority_queue<Item> dijk;
  dijk.emplace(1, 0);
  while(!dijk.empty()) {
    auto [u, d] = dijk.top();
    dijk.pop();
    if(dist[u] != INFLL) continue;
    dist[u] = d;
    for(auto [v, c] : adj[u]) {
      if(dist[v] != INFLL) continue;
      dijk.emplace(v, d + c);
    }
  }

  vector<pair<ll,int>> order;
  for(int i=0; i<q; i++) {
    int t;
    cin >> t;
    order.emplace_back(dist[t], t);
  }
  sort(order.begin(), order.end());
  while(!order.empty() && order.back().first == INFLL) {
    order.pop_back();
  }

  int need = min(k, len);
  if(need <= order.size()) {
    cout << 2 * order[need-1].first << nl;
  } else {
    cout << -1 << nl;
  }

  return 0;
}
