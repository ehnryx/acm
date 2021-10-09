#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

const int L = 18;
const int N = 2e5+1;

vector<int> adj[N];

int ans[N], cnt[N];

struct SegTree {
  int n; int *lazy, *col;
  SegTree(int len) { n = 1<<(32-__builtin_clz(len));
    lazy = new int[2*n]; fill(lazy, lazy+2*n, 0);
    col = new int[2*n]; fill(col, col+2*n, 0);
  }

  void push(int i) {
    if (lazy[i]) {
      lazy[2*i] = lazy[2*i+1] = lazy[i];
      col[2*i] = col[2*i+1] = lazy[i];
      lazy[i] = 0;
    }
  }

  void pull(int i) {
    if (col[2*i] == col[2*i+1]) {
      col[i] = col[2*i];
    } else {
      col[i] = -1;
    }
  }

  // UPDATE
  void update(int a, int b, int v, int i, int l, int r) {
    if (b<l || r<a) return;
    if (a<=l && r<=b && col[i] != -1) {
      // update old
      if (col[i] != 0) {
        ans[cnt[col[i]]]--;
        cnt[col[i]] -= r-l+1;
        ans[cnt[col[i]]]++;
      }
      // update seg
      col[i] = v;
      lazy[i] = v;
      // update new
      ans[cnt[col[i]]]--;
      cnt[col[i]] += r-l+1;
      ans[cnt[col[i]]]++;
      return;
    }
    push(i);
    int m = (l+r)/2;
    update(a, b, v, 2*i, l, m);
    update(a, b, v, 2*i+1, m+1, r);
    pull(i);
  }
  void update(int a, int b, int v) { update(a,b,v,1,0,n-1); }
};

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
  // ASSUME b IS ANCESTOR OF a, modify for insert_node, query_path, query_node
  int insert_path(int a, int b, int v) { // please expand this when typing
    while (ch[a] != ch[b]) { if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      segt[ch[a]]->update(0, pos[a], v); a = par[root[ch[a]]]; }
    if (pos[a] != pos[b]) { if (d[a] < d[b]) swap(a,b);
      segt[ch[a]]->update(pos[b]+1, pos[a], v); } return b; } // returns lca
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, C, Q;
  cin >> n >> C >> Q;
  ans[0] = C;

  for (int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  HLD::build(1);

  while (Q--) {
    int u, c, m;
    cin >> u >> c >> m;
    HLD::insert_path(1, u, c);
    cout << ans[m] << nl;
  }

  return 0;
}
