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

const int N = 2e5+1;
vector<int> adj[N];
int dist[N];

int diam(int n) {
  memset(dist,-1,sizeof dist);
  queue<int> bfs;
  dist[1]=0;
  bfs.push(1);
  int last=0;
  while(!bfs.empty()) {
    int u = last = bfs.front(); bfs.pop();
    for(int v:adj[u]) {
      if(dist[v]==-1) {
        dist[v]=dist[u]+1;
        bfs.push(v);
      }
    }
  }

  memset(dist,-1,sizeof dist);
  dist[last]=0;
  bfs.push(last);
  while(!bfs.empty()) {
    int u = last = bfs.front(); bfs.pop();
    for(int v:adj[u]) {
      if(dist[v]==-1) {
        dist[v]=dist[u]+1;
        bfs.push(v);
      }
    }
  }
  return dist[last];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=1;i<n;i++) {
    int a,b;
    cin>>a>>b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int d1 = diam(n);

  cin>>n;
  for(int i=1;i<=n;i++) {
    adj[i].clear();
  }
  for(int i=1;i<n;i++) {
    int a,b;
    cin>>a>>b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int d2 = diam(n);

  if (d1 > (d2+1)/2) {
    cout << "GGEZ" << nl;
  } else {
    cout << "FF" << nl;
  }

  return 0;
}
