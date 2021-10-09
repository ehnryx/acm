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
const ll MOD = 5318008;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ll CAP = 1e18;

const int N = 5e3+1;
ll dp[N][N];
inline int solve(int n, int a, int b, int ub) {
  fill(dp[0], dp[0]+ub, 0);
  dp[0][a-1] = 1;
  for(int i=1;i<=n;i++) {
    for(int j=0;j<ub;j++) {
      dp[i][j] = dp[i-1][j];
      if(j>0) dp[i][j] += dp[i-1][j-1];
      if(j+1<ub) dp[i][j] += dp[i-1][j+1];
      if(dp[i][j] > CAP) dp[i][j] %= MOD;
    }
  }
  return dp[n][b-1] % MOD;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    int n;
    cin>>n;
    int a,b,x,y;
    cin>>a>>b>>x>>y;
    if(abs(a-x)<abs(b-y)) {
      swap(a,b);
      swap(x,y);
    }
    cout<<solve(abs(a-x),b,y,n)<<nl;
  }

  return 0;
}
