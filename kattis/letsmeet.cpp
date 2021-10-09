#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef double ld;
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

const int N = 20;
const int T = 465;
bool adj[N][N];
ld dp[T][N][N];
int deg[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  for(int i=0;i<m;i++) {
    int a,b;
    cin>>a>>b;
    adj[a][b] = adj[b][a] = true;
    deg[a]++;
    deg[b]++;
  }
  int x,y;
  cin>>x>>y;
  if(x==y) {
    cout<<0<<nl;
    return 0;
  }

  ld ans = 0;
  dp[0][x][y] = 1;
  for(int t=1;t<T;t++) {
    for(int i=0;i<n;i++) {
      for(int j=0;j<n;j++) {
        for(int ii=0;ii<n;ii++) {
          if(!adj[ii][i]) continue;
          for(int jj=0;jj<n;jj++) {
            if(!adj[jj][j]) continue;
            dp[t][i][j] += dp[t-1][ii][jj]/deg[ii]/deg[jj];
          }
        }
        if(dp[t][i][j]<EPS) dp[t][i][j] = 0;
      }
    }
    for(int i=0;i<n;i++) {
      ans += dp[t][i][i]*t;
      dp[t][i][i] = 0;
    }
  }
  if(ans<0.5) cout<<"never meet"<<nl;
  else cout<<ans<<nl;

  return 0;
}
