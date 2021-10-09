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

struct Point {
  int t,s,e,m;
  bool operator < (const Point& o) const {
    return e < o.e;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int g,n,r;
  cin>>g>>n>>r;

  int adj[n+1][n+1];
  memset(adj,INF,sizeof adj);
  for(int i=0;i<r;i++) {
    int a,b,c;
    cin>>a>>b>>c;
    adj[a][b] = min(adj[a][b], c);
    adj[b][a] = min(adj[b][a], c);
  }
  for(int i=1;i<=n;i++) {
    adj[i][i] = 0;
  }
  for(int k=1;k<=n;k++) {
    for(int i=1;i<=n;i++) {
      for(int j=1;j<=n;j++) {
        adj[i][j] = min(adj[i][j], adj[i][k]+adj[k][j]);
      }
    }
  }

  vector<Point> p;
  for(int i=0;i<g;i++) {
    int t,s,e,m;
    cin>>t>>s>>e>>m;
    p.push_back({t,s,e,m});
  }
  sort(p.begin(),p.end());

  map<int,ll> dp[n+1];
  for(int i=1;i<=n;i++) {
    dp[i][-INF*2] = -INFLL;
  }
  dp[1][0] = 0;
  for(const Point& it:p) {
    map<int,ll>& cur = dp[it.t];
    if(!cur.count(it.e)) cur[it.e] = -INFLL;
    for(int i=1;i<=n;i++) {
      int t = it.s-adj[i][it.t];
      cur[it.e] = max(cur[it.e], prev(dp[i].upper_bound(t))->second+it.m);
    }
    cur[it.e] = max(cur[it.e], prev(cur.find(it.e))->second);
  }

  ll ans = 0;
  for(int i=1;i<=n;i++) {
    ans = max(ans,dp[i].rbegin()->second);
  }
  cout<<ans<<nl;

  return 0;
}
