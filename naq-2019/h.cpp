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

const int N = 500+1;
int adj[N][N];
int dp[N][N];

int n;
int solve(int l, int r) {
  if(l>=r) return 0;
  if(dp[l][r]!=-1) return dp[l][r];

  int res = max(solve(l+1,r), solve(l,r-1));
  for(int i=l;i<=r;i++) {
    if(i>l && adj[l][i]) {
      res = max(res, 1+solve(l+1,i-1)+solve(i+1,r));
    }
    if(i<r && adj[r][i]) {
      res = max(res, 1+solve(l,i-1)+solve(i+1,r-1));
    }
  }
  return dp[l][r] = res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  cin>>n;
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      cin>>adj[i][j];
    }
  }

  memset(dp,-1,sizeof dp);
  cout<<solve(0,n-1)<<nl;

  return 0;
}
