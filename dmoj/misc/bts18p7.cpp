// 42 minutes

#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;

struct Node {
	int maxv, sum;
	Node(int m=0, int s=0): maxv(m), sum(s) {}
};

const int N = 1e5+1;

vector<int> adj[N];
struct SegTree {
	int n; Node *segt;
	SegTree(int len) {
		n = (len > 1 ? 1 << (32-__builtin_clz(len-1)) : 1);
		segt = new Node[2*n]; fill(segt, segt+2*n, Node());
	}

	void insert(int x, int v) {
		x += n;
		segt[x].maxv = v;
		for(x/=2; x; x/=2) {
			segt[x].maxv = max(segt[x].maxv, v);
		}
	}

	void remove(int x) {
		x += n;
		segt[x].sum = 1;
		for(x/=2; x; x/=2) {
			segt[x].sum += 1;
		}
	}

	int get_sum(int l, int r) {
		int res = 0;
		for(l+=n, r+=n+1; l<r; l/=2, r/=2) {
			if(l&1) res += segt[l++].sum;
			if(r&1) res += segt[--r].sum;
		}
		return res;
	}

	int query_left(int l, int r, int k) {
		return query_left(l, r, k, 1, 0, n-1);
	}
	int query_left(int l, int r, int k, int i, int s, int e) {
		if(r<s || e<l || segt[i].maxv<k) return -1;
		if(s == e) return s;
		int m = (s+e)/2;
		int res = query_left(l, r, k, 2*i, s, m);
		if(res == -1) res = query_left(l, r, k, 2*i+1, m+1, e);
		return res;
	}

	int query_right(int l, int r, int k) {
		return query_right(l, r, k, 1, 0, n-1);
	}
	int query_right(int l, int r, int k, int i, int s, int e) {
		if(r<s || e<l || segt[i].maxv<k) return -1;
		if(s == e) return s;
		int m = (s+e)/2;
		int res = query_right(l, r, k, 2*i+1, m+1, e);
		if(res == -1) res = query_right(l, r, k, 2*i, s, m);
		return res;
	}
};

namespace HLD {
	SegTree* segt[N];
	int d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; int dn, cn;
	vector<int> chain[N];
	int dfs(int u, int p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
		for(int x:adj[u]) if (x!=p) sub[u] += dfs(x,u); return sub[u]; }
	void hld(int u, int p) { if(dn==cn) { root[cn]=u; sz[cn++]=0; }
		pos[u] = sz[ch[u]=dn]++; int b=-1, c=-1;
		chain[ch[u]].push_back(u);
		for(int x:adj[u]) if (x!=p && sub[x]>b) b=sub[c=x];
		if(c!=-1) hld(c,u);
		for(int y:adj[u]) if (y!=p && y!=c) { dn++; hld(y,u); } }
	void build(int r) { d[0] = dn = cn = 0; dfs(r,0); hld(r,0);
		for(int i=0; i<cn; i++) { segt[i] = new SegTree(sz[i]); }
	}

	void insert_node(int a, int v) {
		segt[ch[a]]->insert(pos[a], v);
	}
	void remove_node(int a) {
		segt[ch[a]]->remove(pos[a]);
	}

	int get_path(int a, int b) {
		int res = 0;
		while(ch[a] != ch[b]) {
			if(d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
			res += segt[ch[a]]->get_sum(0, pos[a]);
			a = par[root[ch[a]]];
		}
		if(pos[a] != pos[b]) {
			if(d[a] < d[b]) swap(a,b);
			res += segt[ch[a]]->get_sum(pos[b]+1, pos[a]);
		}
		return res;
	}

	int query_path(int a, int b, int k) {
		int last = -1;
		bool rev = false;
		while(ch[a] != ch[b]) {
			if(d[root[ch[a]]] < d[root[ch[b]]]) {
				swap(a,b);
				rev ^= 1;
			}
			if(!rev) {
				int res = segt[ch[a]]->query_right(0, pos[a], k);
				if(res != -1) return chain[ch[a]][res];
			} else {
				int res = segt[ch[a]]->query_left(0, pos[a], k);
				if(res != -1) last = chain[ch[a]][res];
			}
			a = par[root[ch[a]]];
		}
		if(d[a] < d[b]) {
			swap(a,b);
			rev ^= 1;
		}
		if(!rev) {
			int res = segt[ch[a]]->query_right(pos[b], pos[a], k);
			if(res != -1) return chain[ch[a]][res];
		} else {
			int res = segt[ch[a]]->query_left(pos[b], pos[a], k);
			if(res != -1) last = chain[ch[a]][res];
		}
		return last;
	}
}

int p[N];
vector<int> rem[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m, r;
	cin >> n >> m >> r;

	for(int i=1; i<=n; i++) {
		cin >> p[i];
	}

	vector<pair<int,int>> edges;
	for(int i=1; i<n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
		edges.push_back(make_pair(a,b));
	}

	HLD::build(1);
	for(int i=1; i<=n; i++) {
		HLD::insert_node(i, p[i]);
	}

	for(int i=0; i<r; i++) {
		int x, y;
		cin >> x >> y;
		auto [a,b] = edges[y-1];
		if(HLD::d[a] < HLD::d[b]) {
			swap(a,b);
		}
		rem[x].push_back(a);
	}

	for(int i=1; i<=m; i++) {
		int a, b, k;
		cin >> a >> b >> k;
		if(HLD::get_path(a, b) > 0) {
			cout << -1 << nl;
		} else {
			cout << HLD::query_path(a, b, k) << nl;
		}
		for(int v : rem[i]) {
			HLD::remove_node(v);
		}
	}

	return 0;
}
