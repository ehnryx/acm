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

struct Edge {
  int i; ll d;
  bool operator < (const Edge& o) const {
    return d > o.d;
  }
};

struct MSTE {
  int a, b; ll c;
  bool operator < (const MSTE& o) const {
    return c < o.c;
  }
};

const int N = 1e5+1;
ll dist[N];
vector<Edge> graph[N];
vector<int> adj[N];

int dsu[N];
int find(int i) {
  if(dsu[i]==0) return i;
  return dsu[i] = find(dsu[i]);
}
int link(int i, int j) {
  if(find(i)==find(j)) return 0;
  dsu[find(i)] = find(j);
  return 1;
}

struct SegTree { int n; ll *segt; // EXAMPLE
  SegTree(int len) { n = 1<<(32-__builtin_clz(len));
    segt = new ll[2*n]; fill(segt, segt+2*n, 0);
  }
  void update(int x, ll v) {
    segt[x+=n] = v;
    for(x/=2; x>0; x/=2) {
      segt[x] = max(segt[2*x], segt[2*x+1]);
    }
  }
  ll query(int l, int r) {
    ll res = 0;
    for(l+=n,r+=n+1; l<r; l/=2,r/=2) {
      if(l&1) res = max(res, segt[l++]);
      if(r&1) res = max(res, segt[--r]);
    }
    return res;
  }
};

namespace HLD { SegTree* segt[N];
  int d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; int dn, cn;
  int dfs(int u, int p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
    for (int x:adj[u]) if (x!=p) sub[u] += dfs(x,u); return sub[u]; }
  void hld(int u, int p) { if (dn == cn) { root[cn]=u; sz[cn++]=0; }
    pos[u] = sz[ch[u]=dn]++; int b=-1, c=-1;
    for (int x:adj[u]) if (x!=p && sub[x]>b) b=sub[c=x]; if (c!=-1) hld(c,u);
    for (int y:adj[u]) if (y!=p && y!=c) { dn++; hld(y,u); } }
  void build(int r) { d[0] = dn = cn = 0; dfs(r,0); hld(r,0);
    for (int i=0; i<cn; i++) segt[i] = new SegTree(sz[i]); }
  // Returns LCA of path ab, MODIFY for insert_node, query_path, query_node
  ll query_path(int a, int b) {
    ll res = 0;
    while (ch[a] != ch[b]) { if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      res = max(res, segt[ch[a]]->query(0, pos[a])); a = par[root[ch[a]]]; }
    if (pos[a] != pos[b]) { if (d[a] < d[b]) swap(a,b);
      res = max(res, segt[ch[a]]->query(pos[b]+1, pos[a])); }
    return res;
  }
  void insert_node(int a, ll v) {
    segt[ch[a]]->update(pos[a], v);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m,k,q;
  cin>>n>>m>>k>>q;
  vector<MSTE> edges;
  for(int i=0;i<m;i++) {
    int a,b,c;
    cin>>a>>b>>c;
    graph[a].push_back({b,c});
    graph[b].push_back({a,c});
    edges.push_back({a,b,c});
  }

  priority_queue<Edge> dijk;
  for(int i=1;i<=k;i++) {
    dijk.push({i,0});
  }
  for(int i=k+1;i<=n;i++) {
    dist[i] = INFLL;
  }
  while(!dijk.empty()) {
    Edge cur = dijk.top();
    dijk.pop();
    if(cur.d > dist[cur.i]) continue;
    for(const Edge& e:graph[cur.i]) {
      if(e.d + cur.d < dist[e.i]) {
        dist[e.i] = e.d + cur.d;
        dijk.push({e.i, dist[e.i]});
      }
    }
  }

  for(MSTE& e : edges) {
    e.c += dist[e.a] + dist[e.b];
  }
  sort(edges.begin(), edges.end());

  vector<MSTE> hlde;
  for(const MSTE& e : edges) {
    if(link(e.a, e.b)) {
      adj[e.a].push_back(e.b);
      adj[e.b].push_back(e.a);
      hlde.push_back(e);
    }
  }

  HLD::build(1);
  for(const MSTE& e : hlde) {
    if(HLD::par[e.a] == e.b) {
      HLD::insert_node(e.a, e.c);
    } else {
      assert(HLD::par[e.b] == e.a);
      HLD::insert_node(e.b, e.c);
    }
  }

  for(int i=0;i<q;i++) {
    int a,b;
    cin>>a>>b;
    cout<<HLD::query_path(a, b)<<nl;
  }

  return 0;
}
