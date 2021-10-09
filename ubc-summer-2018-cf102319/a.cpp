#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  int l,r;
  cin>>l>>r;
  int a[n];
  for(int i=0;i<n;i++) {
    cin>>a[i];
  }

  int dp[r+1];
  memset(dp,INF,sizeof dp);
  dp[0] = 0;
  for(int i=1;i<=r;i++) {
    for(int k:a) {
      if(i-k>=0) {
        dp[i] = min(dp[i], dp[i-k]+1);
      }
    }
  }

  int best = 0;
  int bestv = 0;
  for(int i=l;i<=r;i++) {
    best += dp[i];
  }
  for(int v=1;v<=r;v++) {
    int cur = 0;
    for(int i=l;i<=r;i++) {
      int val = INF;
      for(int j=0;j*v<=r;j++) {
        if(i-j*v>=0) {
          val = min(val, dp[i-j*v]+j);
        }
      }
      cur += val;
    }
    if(cur<best) {
      best = cur;
      bestv = v;
    }
  }
  cout<<bestv<<nl;

  return 0;
}
