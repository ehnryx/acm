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

pii merge(int mode, int cnt, pii o) {
  if(mode == o.first) {
    return make_pair(mode, cnt + o.second);
  } else if(cnt > o.second) {
    return make_pair(mode, cnt - o.second);
  } else {
    return make_pair(o.first, o.second - cnt);
  }
}

int sparse_count(const unordered_map<int,vector<int>>& mp, int v, int l, int r) {
  if(!mp.count(v)) return 0;
  const auto& vec = mp.at(v);
  auto lb = lower_bound(vec.begin(), vec.end(), l);
  auto rb = upper_bound(vec.begin(), vec.end(), r);
  return rb - lb;
}

struct SegTree {
  int n;
  pii* segt;
  SegTree(int len) {
    n = 1<<(32-__builtin_clz(len));
    segt = new pii[2*n];
    fill(segt, segt+2*n, pii(0,0));
  }
  void update(int i, int v) {
    segt[i+n] = make_pair(v, 1);
  }
  void pull(int i) {
    segt[i] = merge(segt[2*i].first, segt[2*i].second, segt[2*i+1]);
  }
  void build() {
    for(int i=n-1; i>0; i--) {
      pull(i);
    }
  }
  pii query(int l, int r) {
    pii res(0, 0);
    for(l+=n, r+=n+1; l<r; l/=2, r/=2) {
      if(l&1) res = merge(res.first, res.second, segt[l++]);
      if(r&1) res = merge(res.first, res.second, segt[--r]);
    }
    return res;
  }
};

const int N = 250000 + 1;
vector<int> adj[N];

namespace HLD { SegTree* segt[N]; unordered_map<int,vector<int>> idx[N];
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
  void insert_node(int u, int v) {
    segt[ch[u]]->update(pos[u], v);
    idx[ch[u]][v].push_back(pos[u]);
  }
  void build_tree() {
    for(int i=0; i<cn; i++) {
      segt[i]->build();
      for(auto& it : idx[i]) {
        sort(it.second.begin(), it.second.end());
      }
    }
  }

  pii query_path(int a, int b) {
    int mode = 0;
    int cnt = 0;
    int len = 0;
    while (ch[a] != ch[b]) {
      if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      pii valcur = segt[ch[a]]->query(0, pos[a]);
      tie(mode, cnt) = merge(mode, cnt, valcur);
      len += pos[a] + 1;
      a = par[root[ch[a]]];
    }
    if (d[a] < d[b]) swap(a,b);
    pii valcur = segt[ch[a]]->query(pos[b], pos[a]);
    tie(mode, cnt) = merge(mode, cnt, valcur);
    len += pos[a] - pos[b] + 1;
    return make_pair(mode, len);
  }

  int query_mode(int a, int b, int v) {
    int res = 0;
    while (ch[a] != ch[b]) {
      if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      res += sparse_count(idx[ch[a]], v, 0, pos[a]);
      a = par[root[ch[a]]];
    }
    if (d[a] < d[b]) swap(a,b);
    res += sparse_count(idx[ch[a]], v, pos[b], pos[a]);
    return res;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, q;
  cin >> n >> q;
  int val[n+1];
  for(int i=1; i<=n; i++) {
    cin >> val[i];
  }
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  HLD::build(1);
  for(int i=1; i<=n; i++) {
    HLD::insert_node(i, val[i]);
  }
  HLD::build_tree();

  for(int i=0; i<q; i++) {
    int a, b;
    cin >> a >> b;
    auto [mode, len] = HLD::query_path(a, b);
    int cnt = HLD::query_mode(a, b, mode);
    if(2*cnt > len) {
      cout << mode << nl;
    } else {
      cout << -1 << nl;
    }
  }

  return 0;
}
