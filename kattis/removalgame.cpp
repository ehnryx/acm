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

const int N = 100;
int a[N];
int dp[N][N][2];
int n;
int solve(int l, int r, int w) {
  if(dp[l][r][w]!=-1) return dp[l][r][w];
  assert(l!=r);
  if(r-l==1) return (w ? 2*__gcd(a[l],a[r]) : 0);
  int res = INF;
  int add = __gcd(a[l],a[r]);
  for(int i=l+1;i<r;i++) {
    if(w) {
      res = min(res, add + solve(l,i,0) + solve(i,r,1));
      res = min(res, add + solve(l,i,1) + solve(i,r,0));
      if(add>0) res = min(res, 3*add + solve(l,i,0) + solve(i,r,0));
    } else {
      res = min(res, add + solve(l,i,0) + solve(i,r,0));
    }
  }
  return dp[l][r][w] = res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  for(;cin>>n&&n;) {
    for(int i=0;i<n;i++) {
      cin>>a[i];
    }
    if(n==2) {
      cout<<__gcd(a[0],a[1])<<nl;
    } else {
      memset(dp,-1,sizeof dp);
      cout<<solve(0,n-1,1)-__gcd(a[0],a[n-1])<<nl;
    }
  }

  return 0;
}
