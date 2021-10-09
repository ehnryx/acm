#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  int a[n+1];
  for(int i=1;i<=n;i++) {
    cin>>a[i];
  }

  ld dp[n+1][6*n+1];
  fill(&dp[0][0], &dp[0][0]+(n+1)*(6*n+1), 0);
  dp[0][0] = 1;
  for(int i=1;i<=n;i++) {
    for(int j=0;j<=6*n;j++) {
      for(int k=1;k<=6;k++) {
        if(j-k>=0) {
          dp[i][j] += dp[i-1][j-k]/6;
        }
      }
    }
  }

  int cdp[n+1][6*n+1][n+1];
  memset(cdp, false, sizeof cdp);
  cdp[0][0][0] = true;
  for(int i=1;i<=n;i++) {
    for(int j=0;j<=6*n;j++) {
      for(int k=0;k<=n;k++) {
        cdp[i][j][k] |= cdp[i-1][j][k];
        if(j-a[i]>=0) {
          cdp[i][j][k] |= cdp[i-1][j-a[i]][k-1];
        }
      }
    }
  }

  ld best = 0;
  int ans = 0;
  for(int s=0;s<=m;s++) {
    for(int i=0;i<=n;i++) {
      if(cdp[n][s][i]) {
        if(dp[n-i][m-s]>best || (dp[n-i][m-s]==best && n-i<ans)) {
          best = dp[n-i][m-s];
          ans = n-i;
        }
      }
    }
  }
  cout<<ans<<nl;

  return 0;
}
