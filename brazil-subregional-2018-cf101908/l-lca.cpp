#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

const int L = 17;
const int N = 1<<L;

vector<int> adj[N];

struct SegTree {
  int n; int *t, *d;
  SegTree(int len) {
    n = 1<<(32-__builtin_clz(len));
    t = new int[2*n]; d = new int[2*n];
    fill(t, t+2*n, 0); fill(d, d+2*n, 0);
  }
	void push(int i, int len) {
		if (d[i]) {
			t[(i<<1)]+=len*d[i]; t[(i<<1|1)]+=len*d[i];
			d[(i<<1)]+=d[i]; d[(i<<1|1)]+=d[i];
			d[i] = 0;
		}
	}
	void pull(int i) {
		t[i] = t[(i<<1)] + t[(i<<1|1)];
	}
  void update(int l, int r, int v) { insert(l,r,v,1,0,n-1); }
	void insert(int l, int r, int v, int i, int s, int e) {
		if (e<l || s>r) return;
		int len = e-s+1;
		if (l<=s && e<=r) {
			t[i] += len*v;
			d[i] += v;
			return;
		}
		push(i, len/2);
		int m = (s+e)/2;
		insert(l, r, v, i<<1, s, m);
		insert(l, r, v, i<<1|1, m+1, e);
		pull(i);
	}
  int query(int l, int r) { return query(l,r,1,0,n-1); }
	int query(int l, int r, int i, int s, int e) {
		if (e<l || s>r) return 0;
		if (l<=s && e<=r) {
			return t[i];
		}
		push(i, (e-s+1)/2);
		int m = (s+e)/2;
		return query(l, r, i<<1, s, m) + query(l, r, i<<1|1, m+1, e);
	}
};

namespace HLD {
  SegTree* segt[N];
  int d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; int dn, cn;
  int dfs(int u, int p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
    for (int x:adj[u]) if (x!=p) sub[u] += dfs(x,u); return sub[u]; }
  void hld(int u, int p) { if (dn == cn) { root[cn]=u; sz[cn++]=0; }
    pos[u] = sz[ch[u]=dn]++; int b=-1, c=-1;
    for (int x:adj[u]) if (x!=p && sub[x]>b) { b = sub[c=x]; }
    if (c!=-1) hld(c,u);
    for (int y:adj[u]) if (y!=p && y!=c) { dn++; hld(y,u); } }
  void build(int r) { d[0] = dn = cn = 0; dfs(r,0); hld(r,0);
    for (int i=0; i<cn; i++) segt[i] = new SegTree(sz[i]); }

  // ASSUME b IS ANCESTOR OF a, modify for insert_node, query_path, query_node
  int insert_path(int a, int b, int v) {
    while (ch[a] != ch[b]) { if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      segt[ch[a]]->update(0, pos[a], v);
      a = par[root[ch[a]]];
    }
    if (pos[a] != pos[b]) { if (d[a] < d[b]) swap(a,b);
      segt[ch[a]]->update(pos[b]+1, pos[a], v);
    }
    return b;
  }
	void insert_node(int a, int v) {
    segt[ch[a]]->update(pos[a], pos[a], v);
	}
  // ASSUME b IS ANCESTOR OF a, modify for insert_node, query_path, query_node
  int query_path(int a, int b, int& ret) {
		int sum = 0;
    while (ch[a] != ch[b]) { if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      sum += segt[ch[a]]->query(0, pos[a]); // call segtree
      a = par[root[ch[a]]];
    }
    if (pos[a] != pos[b]) { if (d[a] < d[b]) swap(a,b);
      sum += segt[ch[a]]->query(pos[b]+1, pos[a]); // call segree
    }
		ret = b;
		return sum;
  }
	int query_node(int a) {
		return segt[ch[a]]->query(pos[a], pos[a]);
	}
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, q;
	cin >> n >> q;

	int a, b, c, d;
	for (int i=1; i<n; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	HLD::build(1);

	while (q--) {
		cin >> a >> b >> c >> d;
		// set
    int lca = HLD::insert_path(a,b,1);
		HLD::insert_node(lca, 1);
		// query
		int ans = 0;
		int lca2;
    ans += HLD::query_path(c,d,lca2);
    ans += HLD::query_node(lca2);
		// reset
    HLD::insert_path(a,b,-1);
    HLD::insert_node(lca,-1);
		// output
		cout << ans << nl;
	}

	return 0;
}
