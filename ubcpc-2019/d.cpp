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

struct Node {
  int i, d;
  bool operator < (const Node& o) const {
    return d>o.d;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  int l[n],r[n];
  for(int i=1;i<=m;i++) {
    cin>>r[i];
  }
  for(int i=1;i<=m;i++) {
    cin>>l[i];
  }

  int dist[2*m+1];
  dist[m] = 0;
  for(int i=1;i<=m;i++) {
    dist[m-i] = l[i];
    dist[m+i] = r[i];
  }

  for(int it=0;it<12;it++) {
    for(int i=1;i<=m;i++) {
      for(int j=0;j<=2*m;j++) {
        if(j-i>=0) dist[j-i] = min(dist[j-i], dist[j]+dist[m-i]);
        if(j+i<=2*m) dist[j+i] = min(dist[j+i], dist[j]+dist[m+i]);
      }
    }
  }

  for(int i=1;i<=m;i++) {
    l[i] = dist[m-i];
    r[i] = dist[m+i];
  }

  int dp[n][2];
  memset(dp,INF,sizeof dp);
  dp[0][0] = dp[0][1] = 0;
  for(int d=1;d<n;d++) {
    for(int i=0;i<=d;i++) {
      if(i>0 && i<=m) {
        dp[d][0] = min(dp[d][0], r[i] + max(dp[i-1][1], dp[d-i][0]));
      }
      if(i<d && d-i<=m) {
        dp[d][1] = min(dp[d][1], l[d-i] + max(dp[i][1], dp[d-1-i][0]));
      }
    }
  }
  cout<<dp[n-1][0]<<nl;

  return 0;
}
