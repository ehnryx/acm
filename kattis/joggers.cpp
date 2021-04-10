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

const int N = 5e4 + 1;
vector<pair<int,int>> adj[N];
bool have[N];
int dp[N][2];

int solve(int u, int p, int must, int s) {
  if(dp[u][must] != -1) return dp[u][must];
  if(s <= 0) return dp[u][must] = (must && !have[u]);
  int put = !have[u];
  int skip = 0;
  for(auto [v, c] : adj[u]) {
    if(v == p) continue;
    put += solve(v, u, false, s - c);
    skip += solve(v, u, true, s - c);
  }
  return dp[u][must] = (must ? put : min(put, skip));
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

  int n, s;
  cin >> n >> s;
  for(int i=1; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, 2*c);
    adj[b].emplace_back(a, 2*c);
  }
  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int v;
    cin >> v;
    have[v] = true;
  }
  memset(dp, -1, sizeof dp);
  cout << solve(1, 0, 0, s) << nl;

  return 0;
}
