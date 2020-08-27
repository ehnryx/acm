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

  int n;
  cin >> n;
  vector<int> t(n+1);
  for(int i=1; i<=n; i++) {
    cin >> t[i];
  }

  vector<int> dp(n+1, INF);
  dp[0] = 0;
  for(int i=1; i<=n; i++) {
    int open = INF;
    int close = 0;
    for(int j=i; j<=n; j++) {
      open = min(open, t[j] + 30*60 - (j-i)*20);
      close = max(close, t[j] + 20);
      int cur = max(close, open + 20*(j-i+1));
      dp[j] = min(dp[j], dp[i-1] + cur - open + 120);
    }
  }
  cout << dp[n] << nl;

  return 0;
}
