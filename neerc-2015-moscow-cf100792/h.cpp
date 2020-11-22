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

const int M = 2e3 + 1;

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
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> hex >> a[i];
  }

  ll ac = -1;
  if(n < M) {
    vector dp(M, vector<int>(M, -INF));
    for(int i=0; i<n; i++) {
      for(int j=0; j<=i; j++) {
        if(i > 0) {
          dp[i][j] = dp[i-1][j];
        }
        if(j == 0) {
          dp[i][j] = max(dp[i][j], j ^ a[i]);
        } else if(i > 0) {
          dp[i][j] = max(dp[i][j], dp[i-1][j-1] + (j ^ a[i]));
        }
      }
    }
    ac = *max_element(dp[n-1].begin(), dp[n-1].end());
  }

  vector<ll> dp(M, -INFLL);
  dp[0] = 0;
  for(int i=0; i<n; i++) {
    vector<ll> ndp(M, -INFLL);
    for(int j=0; j<M && j<=i; j++) {
      ndp[j] = dp[j] + ((i-j) ^ a[i]);
      if(j > 0) {
        ndp[j] = max(ndp[j], dp[j-1]);
      }
    }
    // can skip the i-th
    if(i+1 < M) ndp[i+1] = 0;
    dp = move(ndp);
  }

  ll ans = *max_element(dp.begin(), dp.end());
  cout << ans << nl;
  assert(ans >= 0);

  assert(ac < 0 || ac == ans);

  return 0;
}
