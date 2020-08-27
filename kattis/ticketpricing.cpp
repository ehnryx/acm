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

const int N = 300 + 1;
const int W = 60;
const int K = 100;
int cost[W][K], sold[W][K];
int dp[W][N];

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

  int n, w;
  cin >> n >> w;

  for(int i=0; i<=w; i++) {
    int k;
    cin >> k;
    for(int j=0; j<k; j++) {
      cin >> cost[i][j];
    }
    for(int j=0; j<k; j++) {
      cin >> sold[i][j];
    }
  }

  memset(dp, 0x3f ^ 0xff, sizeof dp);
  memset(dp[w+1], 0, sizeof dp[w+1]);
  for(int i=w; i>=0; i--) {
    for(int j=0; j<=n; j++) {
      for(int k=0; k<K && cost[i][k]; k++) {
        int sell = min(j, sold[i][k]);
        dp[i][j] = max(dp[i][j], dp[i+1][j-sell] + sell * cost[i][k]);
      }
    }
  }

  cout << dp[0][n] << nl;
  for(int k=0; k<K && cost[0][k]; k++) {
    int sell = min(n, sold[0][k]);
    if(dp[0][n] == dp[1][n-sell] + sell * cost[0][k]) {
      cout << cost[0][k] << nl;
      return 0;
    }
  }
  assert(false);

  return 0;
}
