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

struct Edge {
  int u; ll c;
  bool operator < (const Edge& o) const {
    return c>o.c;
  }
};

const int N = 2e5+1;
vector<Edge> adj[N];
ll dist[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,l,r,c;
  cin>>n>>l>>r>>c;

  int u, v;
  cin >> u >> v;

  int a[n+1];
  unordered_map<int,int> idx;
  int id=n+1;
  for(int i=1;i<=n;i++) {
    cin>>a[i];
    if(!idx.count(a[i])) idx[a[i]]=id++;
    if(i>1) adj[i].push_back({i-1,l});
    if(i<n) adj[i].push_back({i+1,r});
    adj[i].push_back({idx[a[i]],c});
    adj[idx[a[i]]].push_back({i,0});
  }

  memset(dist,-1,sizeof dist);
  priority_queue<Edge> bfs;
  bfs.push({u,0});
  while(!bfs.empty()) {
    Edge cur = bfs.top();bfs.pop();
    if(dist[cur.u]==-1) {
      if(cur.u==v) {
        cout << cur.c << nl;
        return 0;
      }
      dist[cur.u]=cur.c;
      for(const Edge& e:adj[cur.u]) {
        if(dist[e.u]==-1) bfs.push({e.u,e.c+cur.c});
      }
    }
  }
  assert(false);

  return 0;
}
