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

  const int N = 2245;
  int dp[N];
  memset(dp,0,sizeof dp);
  int n;
  cin>>n;
  dp[0] = 1;
  for(int j=0;j<n;j++) {
    int v;
    cin>>v;
    for(int i=N-1;i>=v;i--) {
      dp[i] = dp[i] | dp[i-v];
    }
  }

  for(int i=0;i<N;i++) {
    if(dp[1000+i]) {
      cout<<1000+i<<nl;
      return 0;
    }
    if(dp[1000-i]) {
      cout<<1000-i<<nl;
      return 0;
    }
  }

  return 0;
}
