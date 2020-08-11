#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+1;
const int L = 17;
vector<int> adj[N];

struct SegTree {
  int n; ll *segt;
  SegTree(int len) {
    n = 1 << (32-__builtin_clz(len));
    segt = new ll[2*n];
    fill(segt, segt+2*n, 0);
  }
	void update(int x, int v) {
		for (segt[x+=n]=v; x>1; x/=2) {
			segt[x/2] = segt[x]+segt[x^1];
		}
	}
	int query(int l, int r) {
		vector<int> stk;
		for (l+=n, r+=n+1; l<r; l/=2, r/=2) {
			if (l&1) { if (segt[l]) return get_ans(l); else l++; }
			if (r&1) { stk.push_back(--r); }
		}
		for (int i=stk.size()-1; i>=0; i--) {
			if (segt[stk[i]]) return get_ans(stk[i]);
		}
		return -1;
	}
	int get_ans(int x) {
		while (x<n) {
			if (segt[2*x]>0) x*=2;
			else x=x*2+1;
		}
		return segt[x];
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
  int query_path(int a, int b) {
		int res = -1;
    while(ch[a]!=ch[b]) { if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
			int cur = segt[ch[a]]->query(0,pos[a]);
			if (cur != -1) res = cur;
			a=par[root[ch[a]]];
		}
    if (pos[a]!=pos[b]) { if (d[a]<d[b]) swap(a,b);
			int cur = segt[ch[a]]->query(pos[b]+1, pos[a]);
			if (cur != -1) res = cur;
		}
		return res;
	}
	void insert_node(int x, int v) { segt[ch[x]]->update(pos[x], v); }
	int query_node(int x) { return segt[ch[x]]->query(pos[x], pos[x]); }
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, q;
	cin >> n >> q;

	for (int i=1; i<n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	HLD::build(1);

	vector<int> active(n+1, 0);
	while (q--) {
		int t, v;
		cin >> t >> v;
		if (t) {
			int res = HLD::query_path(1,v);
			int cur = HLD::query_node(1);
			if (cur != -1) res = cur;
			cout << res << nl;
		} else {
			if (active[v]) HLD::insert_node(v, active[v]=0);
			else HLD::insert_node(v, active[v]=v);
		}
	}

	return 0;
}
