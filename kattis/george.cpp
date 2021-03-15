//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  int s, t, k, g;
  cin >> s >> t >> k >> g;

  vector<int> go(g);
  for(int i=0; i<g; i++) {
    cin >> go[i];
  }

  vector<vector<pair<int,int>>> adj(n + 1);
  map<pair<int,int>,int> length;
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
    length[make_pair(a, b)] = c;
    length[make_pair(b, a)] = c;
  }

  map<pair<int,int>,pair<int,int>> blocked;
  for(int i=1, c=0; i<g; i++) {
    int len = length[make_pair(go[i-1], go[i])];
    blocked[make_pair(go[i-1], go[i])] = make_pair(c, c + len);
    blocked[make_pair(go[i], go[i-1])] = make_pair(c, c + len);
    c += len;
  }

  struct Item {
    int u, d;
    Item(int _u=0, int _d=0): u(_u), d(_d) {}
    bool operator < (const Item& o) const { return d > o.d; }
  };

  priority_queue<Item> dijk;
  vector<int> dist(n + 1, -1);
  dijk.emplace(s, k);
  while(!dijk.empty()) {
    auto [u, d] = dijk.top();
    dijk.pop();
    if(dist[u] != -1) continue;
    dist[u] = d;
    for(auto [v, c] : adj[u]) {
      if(dist[v] != -1) continue;
      auto [l, r] = blocked[make_pair(u, v)];
      if(l <= d && d < r) {
        dijk.emplace(v, r + c);
      } else {
        dijk.emplace(v, d + c);
      }
    }
  }
  cout << dist[t] - k << nl;

  return 0;
}
