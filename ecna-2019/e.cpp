#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 500+2;
const int K = 11;
int g[N][N],pass[N][N];
int dp[N][N][K];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m,k;
  cin>>n>>m>>k;
  for(int i=1;i<=n;i++) {
    for(int j=1;j<=m;j++) {
      cin>>g[i][j];
    }
  }

  for(int i=2;i<n;i++) {
    for(int j=2;j<m;j++) {
      if(g[i][j-1]==-1||g[i][j+1]==-1) continue;
      if(g[i][j-1]<g[i][j] && g[i][j+1]<g[i][j]
          && g[i-1][j]>g[i][j] && g[i+1][j]>g[i][j]) {
        pass[i][j] = true;
      }
    }
  }

  memset(dp,INF,sizeof dp);
  for(int i=1;i<=n;i++) {
    dp[i][0][0] = 0;
  }
  for(int j=1;j<=m;j++) {
    for(int i=1;i<=n;i++) {
      if(g[i][j]==-1) continue;
      if(pass[i][j]) {
        for(int t=1;t<=k;t++) {
          dp[i][j][t] = min(dp[i][j][t], dp[i][j-1][t-1]+g[i][j]);
          dp[i][j][t] = min(dp[i][j][t], dp[i-1][j-1][t-1]+g[i][j]);
          dp[i][j][t] = min(dp[i][j][t], dp[i+1][j-1][t-1]+g[i][j]);
        }
      } else {
        for(int t=0;t<=k;t++) {
          dp[i][j][t] = min(dp[i][j][t], dp[i][j-1][t]+g[i][j]);
          dp[i][j][t] = min(dp[i][j][t], dp[i-1][j-1][t]+g[i][j]);
          dp[i][j][t] = min(dp[i][j][t], dp[i+1][j-1][t]+g[i][j]);
        }
      }
    }
  }

  int ans = INF;
  for(int i=1;i<=n;i++) {
    ans = min(ans, dp[i][m][k]);
  }
  if(ans==INF) cout<<"impossible"<<nl;
  else cout<<ans<<nl;

  return 0;
}
