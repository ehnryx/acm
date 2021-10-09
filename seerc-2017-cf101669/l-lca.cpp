#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

struct SegTree {
  int n;  int* segt;
  SegTree(int len) {
    n = 1 << (32-__builtin_clz(len));
    segt = new int[2*n];
    fill(segt, segt+2*n, 0); 
  }
  void update(int l, int r, int v) {
    for (l+=n, r+=n+1; l<r; l/=2, r/=2) {
      if (l&1) segt[l++] += v;
      if (r&1) segt[--r] += v;
    }
  }
  int query(int x) {
    int sum = 0;
    for (x+=n; x>0; x/=2) {
      sum += segt[x];
    }
    return sum;
  }
};

const int N = 1e5+1;
const int L = 17;
vector<int> adj[N];

namespace HLD {
  SegTree* segt[N];
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
  int insert_path(int a, int b, int v) { // please expand this when typing
    while (ch[a] != ch[b]) { if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      segt[ch[a]]->update(0, pos[a], v); a = par[root[ch[a]]]; }
    if (pos[a] != pos[b]) { if (d[a] < d[b]) swap(a,b);
      segt[ch[a]]->update(pos[b]+1, pos[a], v); } return b; } // returns lca
  int query_node(int a) { return segt[ch[a]]->query(pos[a]); }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<pii> edges1, edges2;
  for (int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    edges1.push_back({a,b});
  }
  HLD::build(1);

  for (int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    HLD::insert_path(a,b,1);
    edges2.push_back({a,b});
  }

  int one = 0;
  int two = 0;
  for (int i=1; i<=n; i++) {
    int cur = HLD::query_node(i);
    if (cur == 1) one++;
    else if (cur == 2) two++;
  }
  if (one > 0) {
    cout << "2 " << one << nl;
    return 0;
  }

  for (int i=1; i<=n; i++) {
    adj[i].clear();
  }
  for (const pii& it : edges2) {
    adj[it.first].push_back(it.second);
    adj[it.second].push_back(it.first);
  }
  HLD::build(1);

  for (const pii& it : edges1) {
    HLD::insert_path(it.first,it.second,1);
  }

  int other = 0;
  for (int i=1; i<=n; i++) {
    other += (HLD::query_node(i) == 2);
  }
  cout << "3 " << other+two << nl;

  return 0;
}
