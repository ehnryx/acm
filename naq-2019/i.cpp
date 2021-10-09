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
ll adj[N][N];
int rep[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m,t,d;
  cin>>n>>m>>t>>d;
  rep[1] = rep[n] = true;
  for(int i=0;i<t;i++) {
    int v;
    cin>>v;
    rep[v] = true;
  }

  memset(adj,INF,sizeof adj);
  for(int i=0;i<m;i++) {
    int a,b,c;
    cin>>a>>b>>c;
    adj[a][b] = min(adj[a][b], (ll)c);
    adj[b][a] = min(adj[b][a], (ll)c);
  }

  for(int k=1;k<=n;k++) {
    for(int i=1;i<=n;i++) {
      for(int j=1;j<=n;j++) {
        adj[i][j] = min(adj[i][j], adj[i][k]+adj[k][j]);
      }
    }
  }

  for(int i=1;i<=n;i++) {
    for(int j=1;j<=n;j++) {
      if(rep[i]&&rep[j]&&adj[i][j]<=d);
      else adj[i][j] = INFLL;
    }
  }

  for(int k=1;k<=n;k++) {
    for(int i=1;i<=n;i++) {
      for(int j=1;j<=n;j++) {
        adj[i][j] = min(adj[i][j], adj[i][k]+adj[k][j]);
      }
    }
  }

  if(adj[1][n]<INFLL) cout<<adj[1][n]<<nl;
  else cout<<"stuck"<<nl;

  return 0;
}
