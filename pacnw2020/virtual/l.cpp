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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Int {
  ll x;
  Int(ll _x=0): x(_x) {}
  Int operator + (const Int& o) const {
    return Int(min(INFLL, x + o.x));
  }
  Int operator * (const Int& o) const {
    if(x == 0 || o.x == 0) return Int(0);
    if(x > INFLL / o.x + 1) return Int(INFLL);
    return Int(min(INFLL, x * o.x));
  }
};

const int N = 5000 + 1;
vector<int> adj[N];
int sz[N];
Int dp[N][N];
void build(int u, int p) {
  if(p) adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
  sz[u] = 1;
  dp[u][1] = Int(1);
  for(int v : adj[u]) {
    build(v, u);
    for(int j=sz[u]+sz[v]; j>=0; j--) {
      for(int k=max(0,j-sz[u]); k<=min(j,sz[v]); k++) {
        dp[u][j] = dp[u][j] + dp[u][j-k] * dp[v][k];
      }
    }
    sz[u] += sz[v];
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

  int n; ll kth;
  cin >> n >> kth;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  build(1, 0);

  vector<Int> cnt(n+1);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cnt[j] = cnt[j] + dp[i][j];
    }
  }
  for(int i=1; i<=n; i++) {
    if(kth <= cnt[i].x) {
      cout << i << nl;
      return 0;
    }
    kth -= cnt[i].x;
  }
  cout << -1 << nl;

  return 0;
}
