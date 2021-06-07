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

  int n, x, k;
  cin >> n >> x >> k;
  vector<int> h(n+1);
  for(int i=1; i<=n; i++) {
    cin >> h[i];
  }
  vector adj(n+1, vector<int>(n+1));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cin >> adj[i][j];
    }
  }

  struct node {
    int u, v, d;
    bool operator < (const node& o) const { return d > o.d; }
  };
  vector dist(n+1, vector<int>(k+1, -1));
  priority_queue<node> dijk;
  dijk.push({1, k, 0});
  while(!dijk.empty()) {
    auto [u, v, d] = dijk.top();
    dijk.pop();
    if(dist[u][v] != -1) continue;
    dist[u][v] = d;
    for(int i=1; i<=n; i++) {
      int add = max(0, h[i] - h[u]);
      if(add <= v && dist[i][v-add] == -1) {
        dijk.push({i, v - add, d + adj[u][i]});
      }
    }
  }

  int ans = INF;
  for(int i=0; i<=k; i++) {
    if(dist[x][i] != -1) {
      ans = min(ans, dist[x][i]);
    }
  }
  if(ans == INF) {
    cout << -1 << nl;
  } else {
    cout << ans << nl;
  }

  return 0;
}
