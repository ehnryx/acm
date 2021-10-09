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

struct Edge {
  int i; ll d;
  bool operator < (const Edge& o) const {
    return d > o.d;
  }
};

const int N = 2e5+1;
vector<Edge> adj[N], rev[N];
ll to[N], from[N];

void dijkstra(int s, vector<Edge> g[N], ll d[N]) {
  fill(d,d+N,INFLL);
  priority_queue<Edge> dijk;
  dijk.push({s,0});
  d[s] = 0;
  while(!dijk.empty()) {
    Edge cur = dijk.top();
    dijk.pop();
    if(d[cur.i] == cur.d) {
      for(const Edge& e:g[cur.i]) {
        if(cur.d + e.d < d[e.i]) {
          dijk.push({e.i, d[e.i] = cur.d+e.d});
        }
      }
    }
  }
}

int deg[N];
ll len[N];

bool valid(int n, ll s, ll t, ll ub) {
  memset(deg,0,sizeof deg);
  for(int i=1;i<N;i++) {
    if(to[i]<=ub) {
      for(const Edge& e:rev[i]) {
        deg[e.i]++;
      }
    }
  }

  memset(len,-1,sizeof len);
  queue<int> bfs;
  for(int i=1;i<N;i++) {
    if(to[i]<=ub && deg[i]==0) {
      assert(i==n);
      bfs.push(i);
      len[i] = 0;
    }
  }
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(const Edge& e:rev[u]) {
      if(to[e.i]<=ub) {
        len[e.i] = max(len[e.i], len[u] + e.d);
        if(--deg[e.i] == 0) {
          bfs.push(e.i);
        }
      }
    }
  }

  len[1] = -1;
  for(int i=1;i<N;i++) {
    if(to[i]<=ub) {
      if(len[i]==-1) len[i] = INFLL;
      ll buf = ub-to[i];
      if(buf + len[i] >= t-s && from[i] - buf <= s) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  ll s,t;
  cin>>s>>t;

  int n,m;
  cin>>n>>m;
  for(int i=1;i<=m;i++) {
    int a,b,c;
    cin>>a>>b>>c;
    adj[a].push_back({n+i,0});
    adj[n+i].push_back({b,c});
    rev[b].push_back({n+i,c});
    rev[n+i].push_back({a,0});
  }
  dijkstra(1,adj,from);
  dijkstra(n,rev,to);

  ll left = 0;
  ll right = 1e12;
  while(left<right) {
    ll mid = (left+right)/2;
    if(valid(n,s,t,mid)) {
      right = mid;
    } else {
      left = mid+1;
    }
  }
  cout<<left<<nl;

  return 0;
}
