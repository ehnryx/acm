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

  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int> sz(n+1);
  for(int i=1; i<=n; i++) {
    cin >> sz[i];
  }

  struct Item : pair<int,int> {
    Item(int a, int b): pair<int,int>(a, b) {}
    bool operator < (const Item& o) const {
      return tie(second, first) > tie(o.second, o.first);
    }
  };
  priority_queue<Item> dijk;
  vector<bool> vis(n+1);
  int have = sz[1];
  dijk.emplace(1, -1);
  vis[1] = true;
  while(!dijk.empty()) {
    auto [u, c] = dijk.top();
    dijk.pop();
    if(c >= have) break;
    have += max(0, c);
    for(int v : adj[u]) {
      if(vis[v]) continue;
      vis[v] = true;
      dijk.emplace(v, sz[v]);
    }
  }

  cout << have << nl;

  return 0;
}
