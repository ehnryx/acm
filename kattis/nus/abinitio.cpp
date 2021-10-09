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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 4e3+1;
bool adj[N][N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m,k;
  cin>>n>>m>>k;
  for(int i=0;i<m;i++) {
    int a,b;
    cin>>a>>b;
    adj[a][b] = true;
  }

  bool transpose = false;
  bool complement = false;
  while(k--) {
    int t;
    cin>>t;
    //cerr<<"got "<<t<<nl;
    if(t==1) {
      n++;
      for(int i=0;i<n;i++) {
        adj[i][n-1] = adj[n-1][i] = complement;
      }
    } else if(t==2) {
      int a,b;
      cin>>a>>b;
      if(transpose) swap(a,b);
      assert(adj[a][b] != !complement);
      adj[a][b] = !complement;
    } else if(t==3) {
      int x;
      cin>>x;
      for(int i=0;i<n;i++) {
        adj[i][x] = adj[x][i] = complement;
      }
    } else if(t==4) {
      int a,b;
      cin>>a>>b;
      if(transpose) swap(a,b);
      assert(adj[a][b] != complement);
      adj[a][b] = complement;
    } else if(t==5) {
      transpose = !transpose;
    } else {
      complement = !complement;
    }
    //cerr<<"transpose: "<<transpose<<nl;
    //cerr<<"complement: "<<complement<<nl;
    //cerr<<"graph: "<<nl; for(int i=0;i<n;i++) { for(int j=0;j<n;j++) {
      //cerr<<adj[i][j]<<" "; } //cerr<<nl; }
    //cerr<<nl;
  }

  if(transpose) {
    for(int i=0;i<n;i++) {
      for(int j=0;j<i;j++) {
        swap(adj[i][j], adj[j][i]);
      }
    }
  }
  if(complement) {
    for(int i=0;i<n;i++) {
      for(int j=0;j<n;j++) {
        adj[i][j] = !adj[i][j];
      }
    }
  }

  cout<<n<<nl;
  for(int i=0;i<n;i++) {
    int deg = 0;
    ll ha = 0;
    for(int j=n-1;j>=0;j--) {
      if(i==j) continue;
      if(adj[i][j]) {
        deg++;
        ha = (7*ha + j) % MOD;
      }
    }
    cout<<deg<<" "<<ha<<nl;
  }

  return 0;
}
