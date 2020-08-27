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

const int N = 100 + 1;
const int M = 3e4 + 1;
int dp[N][M];
pair<int,int> pre[N][M];

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

  int n;
  cin >> n;
  vector<int> cost(n+1);
  for(int i=1; i<=n; i++) {
    cin >> cost[i];
  }

  dp[0][0] = 1;
  for(int i=1; i<=n; i++) {
    for(int j=0; j<M; j++) {
      dp[i][j] = dp[i-1][j];
      pre[i][j] = make_pair(i-1, j);
      if(j >= cost[i] && dp[i][j-cost[i]]) {
        pre[i][j] = make_pair(i, j-cost[i]);
        dp[i][j] = min(2, dp[i][j] + dp[i][j-cost[i]]);
      }
    }
  }

  int T;
  cin >> T;
  while(T--) {
    int m;
    cin >> m;
    if(dp[n][m] == 0) {
      cout << "Impossible" << nl;
    } else if(dp[n][m] == 2) {
      cout << "Ambiguous" << nl;
    } else {
      vector<int> ans;
      for(int i=n; i>=1; ) {
        auto [ni, nm] = pre[i][m];
        if(ni == i) ans.push_back(i);
        tie(i, m) = tie(ni, nm);
      }
      reverse(ans.begin(), ans.end());
      for(int it : ans) {
        cout << it << " ";
      }
      cout << nl;
    }
  }

  return 0;
}
