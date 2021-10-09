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

const int N = 100+1;
ld dp[N][N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  ld p[n];
  for(int i=0;i<n;i++) {
    cin>>p[i];
  }
  sort(p,p+n,greater<int>());

  ld ans = 0;
  dp[0][0] = 1;
  for(int i=1;i<=n;i++) {
    ld cur = 0;
    for(int j=0;j<=n;j++) {
      if(j>0) {
        dp[i][j] = dp[i-1][j]*(100-p[i-1])/100 + dp[i-1][j-1]*(p[i-1])/100;
        cur += dp[i][j] * pow(j,(ld)j/i);
      } else {
        dp[i][j] = dp[i-1][j]*(100-p[i-1])/100;
      }
    }
    ans = max(ans,cur);
  }
  cout<<ans<<nl;

  return 0;
}
