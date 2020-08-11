#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

const int N = 2e5+1;
vector<int> adj[N];

namespace PATH { 
	struct SegTree { int n; ll* segt;
		SegTree(int len) { n = 1 << (32 - __builtin_clz(len));
			segt = new ll[2*n]; fill(segt, segt+2*n, 0); }
		void update(int x, int v) {
			for (x += n; x > 0; x /= 2) {
				segt[x] += v;
			}
		}
		ll query(int l, int r) {
			ll ans = 0;
			for (l += n, r += n+1; l < r; l/=2, r/=2) {
				if (l&1) ans += segt[l++];
				if (r&1) ans += segt[--r];
			}
			return ans;
		}
	};

	SegTree* segt[N];
	int d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; int dn, cn;
	int dfs(int u, int p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
		for (int x:adj[u]) if (x!=p) sub[u] += dfs(x, u); return sub[u]; }
	void hld(int u, int p) { if (dn == cn) { root[cn]=u; sz[cn++]=0; }
		pos[u] = sz[ch[u]=dn]++; int b=-1, c=-1;
		for (int x:adj[u]) if (x!=p && sub[x]>b) b = sub[c=x]; if (c!=-1) hld(c, u);
		for (int y:adj[u]) if (y!=p && y!=c) { dn++; hld(y, u); } }
	void build(int r) { d[0] = dn = cn = 0; dfs(r, 0); hld(r, 0);
		for (int i=0; i<cn; i++) segt[i] = new SegTree(sz[i]); }

	void insert_node(int a, int v) { segt[ch[a]]->update(pos[a], v); }
	ll query_path(int a, int b) {
		ll ans = 0;
		while (ch[a] != ch[b]) {
			if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a, b);
			ans += segt[ch[a]]->query(0, pos[a]);
			a = par[root[ch[a]]];
		}
		if (pos[a] != pos[b]) {
			if (d[a] < d[b]) swap(a, b);
			ans += segt[ch[a]]->query(pos[b]+1, pos[a]);
		}
		return ans;
	}
}

namespace HLD {
	struct SegTree { int n; int *segt;
		SegTree(int len) { n = 1 << (32 - __builtin_clz(len));
			segt = new int[2*n]; fill(segt, segt+2*n, 0); }
		void update(int l, int r, int v) {
			for (l+=n, r+=n+1; l < r; l /= 2, r /= 2) {
				if (l&1) segt[l++] += v;
				if (r&1) segt[--r] += v;
			}
		}
		int query(int x) {
			int ans = 0;
			for (x += n; x > 0; x /= 2) {
				ans += segt[x];
			}
			return ans;
		}
	};

	SegTree* segt[N];
	int d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; int dn, cn;
	int dfs(int u, int p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
		for (int x:adj[u]) if (x!=p) sub[u] += dfs(x, u); return sub[u]; }
	void hld(int u, int p) { if (dn == cn) { root[cn]=u; sz[cn++]=0; }
		pos[u] = sz[ch[u]=dn]++; int b=-1, c=-1;
		for (int x:adj[u]) if (x!=p && sub[x]>b) b = sub[c=x]; if (c!=-1) hld(c, u);
		for (int y:adj[u]) if (y!=p && y!=c) { dn++; hld(y, u); } }
	void build(int r) { d[0] = dn = cn = 0; dfs(r, 0); hld(r, 0);
		for (int i=0; i<cn; i++) segt[i] = new SegTree(sz[i]); }

	void insert_node(int a, int v = 1) {
		segt[ch[a]]->update(pos[a], pos[a], v);
	}
	int query_node(int a) {
		return segt[ch[a]]->query(pos[a]);
	}
	int insert_path(int a, int b, int v = 1) {
		while (ch[a] != ch[b]) {
			if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a, b);
			segt[ch[a]]->update(0, pos[a], v);
			a = par[root[ch[a]]];
		}
		if (pos[a] != pos[b]) {
			if (d[a] < d[b]) swap(a, b);
			segt[ch[a]]->update(pos[b]+1, pos[a], v);
		}
		insert_node(b, v);
		return b;
	}
}

const int L = 18;
int par[N], dist[N], depth[N];
int anc[N][L];

void precmp(int u, int p) {
	depth[u] = depth[p]+1;
	anc[u][0] = p;
	for (int j=1; j<L; j++) {
		anc[u][j] = anc[anc[u][j-1]][j-1];
	}
	for (int x : adj[u]) {
		if (x != p) {
			precmp(x, u);
		}
	}
}

int jump(int u, int len) {
	for (int i=0; i<L; i++) {
		if (len&1<<i) {
			u = anc[u][i];
		}
	}
	return u;
}

// a, b(anc)
int bs_up(int a, int b, int v) {
	int l = depth[b];
	int r = depth[a];
	while (l < r) {
		int m = (l+r+1)/2;
		int mid = jump(a, depth[a] - m);
		if (HLD::query_node(mid) == v) {
			l = m;
		} else {
			r = m-1;
		}
	}
	assert(l == r);
	return jump(a, depth[a] - l);
}

int bs_down(int a, int b, int v) {
	int l = depth[b]+1;
	int r = depth[a];
	while (l < r) {
		int m = (l+r)/2;
		int mid = jump(a, depth[a] - m);
		if (HLD::query_node(mid) == v) {
			r = m;
		} else {
			l = m+1;
		}
	}
	assert(l == r);
	return jump(a, depth[a] - l);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	for (int i=2; i<=n; i++) {
		cin >> par[i] >> dist[i];
		adj[par[i]].push_back(i);
		adj[i].push_back(par[i]);
	}
	HLD::build(1);
	PATH::build(1);
	precmp(1, 0);

	for (int i=2; i<=n; i++) {
		PATH::insert_node(i, dist[i]);
	}

	ll ans = 0;
	cout << 0 << nl;

	HLD::insert_node(1);
	int a, b, plca; // endpoints of good set
	a = b = plca = 1;
	for (int i=2; i<=n; i++) {
		int maxv = (i+1)/2;
		if (i%2 == 0) {
			ans += PATH::query_path(a, i);
			int lca = HLD::insert_path(a, i);
			HLD::insert_node(a, -1);
			if (HLD::query_node(lca) == maxv) {
				b = bs_up(i, lca, maxv);
				plca = lca;
			} else {
				b = bs_down(a, lca, maxv);
				plca = b;
			}
		}
		else {
			int alca = HLD::insert_path(a, i, 0);
			int blca = HLD::insert_path(b, i, 0);
			if (depth[alca] < depth[blca]) swap(alca, blca);
			if (depth[alca] < depth[plca]) alca = plca;
			ans += PATH::query_path(alca, i);
			HLD::insert_path(alca, i);
			a = b = plca = alca;
		}
		cout << ans << nl;
	}

	return 0;
}
