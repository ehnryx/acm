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

const int N = 1e3+1;
int adj[N][4],aj2[N][4];
bool vis[N][N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=1;i<=n;i++) {
    for(int j=0;j<4;j++) {
      cin>>adj[i][j];
    }
  }
  for(int i=1;i<=n;i++) {
    for(int j=0;j<4;j++) {
      cin>>aj2[i][j];
    }
  }

  queue<pii> bfs;
  bfs.push(pii(1,1));
  vis[1][1] = true;
  while(!bfs.empty()) {
    int a,b;
    tie(a,b) = bfs.front();
    bfs.pop();
    vis[a][b] = true;
    for(int j=0;j<4;j++) {
      int na = adj[a][j];
      int nb = aj2[b][j];
      if(!vis[na][nb]) {
        vis[na][nb] = true;
        bfs.push(pii(na,nb));
      }
    }
  }

  bool ok = false;
  bool no = false;
  for(int i=0;i<=n;i++) {
    ok |= vis[n][i];
    no |= (i!=n && vis[n][i]);
  }
  if(!ok) {
    cout<<"Impossible"<<nl;
  } else if(no) {
    cout<<"No"<<nl;
  } else {
    cout<<"Yes"<<nl;
  }

  return 0;
}
