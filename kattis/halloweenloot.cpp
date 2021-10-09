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

const int N = 100+1;
const int M = 2e4+1;
const int O = 1e4;
int a[N],b[N];
int dp[N][M];
string res[N][M];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=1;i<=n;i++) {
    cin>>a[i];
  }
  for(int i=1;i<=n;i++) {
    cin>>b[i];
  }

  dp[0][O] = true;
  for(int i=1;i<=n;i++) {
    for(int j=0;j<M;j++) {
      if(0<=j-a[i] && j-a[i]<M && dp[i-1][j-a[i]]) {
        dp[i][j] = true;
        res[i][j] = res[i-1][j-a[i]] + "A";
      }
      if(0<=j+b[i] && j+b[i]<M && dp[i-1][j+b[i]]) {
        if(dp[i][j]) {
          res[i][j] = min(res[i][j], res[i-1][j+b[i]] + "B");
        } else {
          dp[i][j] = true;
          res[i][j] = res[i-1][j+b[i]] + "B";
        }
      }
    }
  }

  string ans = "X";
  for(int i=0;O+i<M;i++) {
    if(dp[n][O-i]) ans = min(ans, res[n][O-i]);
    if(dp[n][O+i]) ans = min(ans, res[n][O+i]);
    if(dp[n][O-i]||dp[n][O+i]) break;
  }
  assert(ans!="X");
  cout<<ans<<nl;

  return 0;
}
