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
  int id,c;
};

const int N = 100+1;
const int M = 2*4500+N;
vector<Edge> adj[N];
int dist[N];

namespace MinArb { int from[M], to[M]; ll cost[M], nc[M]; int m = 0;
  int in[2*N], pre[2*N], par[2*N], dsu[2*N], spar[2*N], sin[2*N]; ll sh[2*N]; 
  vector<int> child[2*N]; priority_queue<pair<ll,int>> p[2*N];
  void add_edge(int a, int b, ll c=0) {
    from[m] = a; to[m] = b; nc[m] = -c; cost[m] = c; p[b].push({-c, m++}); }
  void init(int n=N) { m = 0;
    fill(p,p+2*n,priority_queue<pair<ll,int>>());
    fill(child,child+2*n,vector<int>()); }
  int find(int i) { return dsu[i] == -1 ? i : dsu[i] = find(dsu[i]); }
  void link(int i, int j) { if (find(i) != find(j)) dsu[find(i)] = find(j); }
  void contract(int n) { memset(dsu, -1, sizeof dsu);
    memset(in, -1, sizeof in); memset(sh, 0, sizeof sh);
    memset(pre, -1, sizeof pre); memset(par, -1, sizeof par);
    for (int a = n; !p[a].empty(); ) {
      int e = p[a].top().second; p[a].pop(); int u = from[e]; int b = find(u);
      if (a != b) { in[a] = e; pre[a] = b; if (in[u] == -1) a = b; else {
        for (int c = ++n; a != c; a = find(pre[a])) {
          par[a] = c; sh[a] = -nc[in[a]]; child[c].push_back(a);
          if (p[a].size()>p[c].size()) { swap(p[a],p[c]); swap(sh[a],sh[c]); }
          for (ll add = sh[a]-sh[c]; !p[a].empty(); ) { auto it = p[a].top();
            p[a].pop(); p[c].push({it.first + add, it.second});
            nc[it.second] += add; } link(a, c); } } } } } // henryx
  void expand(int r) { stack<int> roots; auto dismantle = [&](int u) {
    for ( ; par[u] != -1; u = par[u]) for (int v : child[par[u]]) {
      if (u!=v) { par[v] = -1; if (!child[v].empty()) roots.push(v); } } };
  for (dismantle(r); !roots.empty(); ) { int c = roots.top(); roots.pop();
    int v = to[in[c]]; in[v] = in[c]; dismantle(v); } }
  void save(int n=N){ for(int i=0;i<2*n;i++){ spar[i]=par[i]; sin[i]=in[i]; }}
  void load(int n=N){ for(int i=0;i<2*n;i++){ par[i]=spar[i]; in[i]=sin[i]; }}
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  unordered_map<string,int> remap;
  remap["English"] = 0;
  for(int i=1;i<=n;i++) {
    string s;
    cin>>s;
    remap[s] = i;
  }

  for(int i=0;i<m;i++) {
    string s,t; int w;
    cin>>s>>t>>w;
    adj[remap[s]].push_back({remap[t],w});
    adj[remap[t]].push_back({remap[s],w});
  }

  fill(dist,dist+N,INF);
  queue<int> bfs;
  bfs.push(0);
  dist[0] = 0;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(const Edge& e:adj[u]) {
      if(dist[e.id]==INF) {
        dist[e.id] = dist[u] + 1;
        bfs.push(e.id);
      }
    }
  }

  for(int i=0;i<=n;i++) {
    MinArb::add_edge(i,(i+1)%(n+1),1LL<<51);
    for(const Edge& e:adj[i]) {
      if(dist[e.id] == dist[i]+1) {
        MinArb::add_edge(i,e.id,e.c);
      }
    }
  }
  MinArb::contract(n);
  MinArb::expand(0);

  ll ans = 0;
  for(int i=1;i<=n;i++) {
    ans += MinArb::cost[MinArb::in[i]];
  }
  if(ans<1LL<<50) {
    cout<<ans<<nl;
  } else {
    cout<<"Impossible"<<nl;
  }

  return 0;
}
