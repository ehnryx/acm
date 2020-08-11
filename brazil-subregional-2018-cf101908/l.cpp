#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

const int L = 18;
const int N = 1<<L;

struct SegmentTree {
	int t[2*N], d[2*N];
	SegmentTree() { memset(t,0,sizeof t); memset(d,0,sizeof d); }
	void push(int i, int len) {
		if (d[i]) {
			t[i<<1]+=len*d[i]; t[i<<1|1]+=len*d[i];
			d[i<<1]+=d[i]; d[i<<1|1]+=d[i];
			d[i] = 0;
		}
	}
	void pull(int i) {
		t[i] = t[i<<1] + t[i<<1|1];
	}
	void insert(int l, int r, int v, int i=1, int s=0, int e=N-1) {
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
	int query(int l, int r, int i=1, int s=0, int e=N-1) {
		if (e<l || s>r) return 0;
		if (l<=s && e<=r) {
			return t[i];
		}
		push(i, (e-s+1)/2);
		int m = (s+e)/2;
		return query(l, r, i<<1, s, m) + query(l, r, i<<1|1, m+1, e);
	}
};
SegmentTree segt;

vector<int> adj[N];

template<class T> struct RMQ {
	T rmq[N][L];
	int lg[N];
	void build() {
		for (int i=1; i<N; i++) {
			lg[i] = 31 - __builtin_clz(i);
		}
		for (int j=1; j<L; j++) 
			for (int i=0; i+(1<<j)-1<N; i++)
				rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
	}
	T query(int l, int r) {
		if (l>r) swap(l,r);
		int j = lg[r-l+1];
		return min(rmq[l][j], rmq[r-(1<<j)+1][j]);
	}
};

struct LCA : RMQ<pii> {
	int depth[N], segpos[N];
	int parent[N], subsz[N];
	int lcanum = 0;
	LCA() {
		lcanum = 0;
		depth[0] = 0;
	}
	void build(int root) {
		build(root, 0);
		RMQ::build();
	}
	int build(int cur, int par) {
		depth[cur] = depth[par]+1;
		segpos[cur] = lcanum;
		parent[cur] = par;
		subsz[cur] = 1;
		RMQ::rmq[lcanum++][0] = pii(depth[cur], cur);
		for (int x : adj[cur]) {
			if (x != par) {
				subsz[cur] += build(x,cur);
				RMQ::rmq[lcanum++][0] = pii(depth[cur], cur);
			}
		}
		return subsz[cur];
	}
	int query(int a, int b) {
		return RMQ::query(segpos[a], segpos[b]).second;
	}
};

struct HLD : LCA {
	vector<int> sz, root, start;
	int chain[N], pos[N];
	int hldnum, segnum;
	HLD(): LCA() {
		hldnum = segnum = 0;
	}
	int get(int i) const { return start[chain[i]]+pos[i]; }
	void build(int root) {
		LCA::build(root);
		build_hld(root, 0);
	}
	void build_hld(int cur, int par) {
		if (hldnum == root.size()) {
			root.push_back(cur);
			start.push_back(segnum);
			sz.push_back(0);
		}
		chain[cur] = hldnum;
		pos[cur] = sz[chain[cur]]++;
		segnum++;
		int best = -1, child = -1;
		for (int x : adj[cur]) {
			if (x != par && subsz[x] > best) {
				best = subsz[x];
				child = x;
			}
		}
		if (child != -1) build_hld(child, cur);
		for (int x : adj[cur]) {
			if (x != par && x != child) {
				hldnum++;
				build_hld(x, cur);
			}
		}
	}

	int query_path(int a, int b) {
		//cerr << "query " << a << " " << b << nl;
		int sum = 0;
		while (chain[a] != chain[b]) {
			int s = start[chain[a]];
			sum += segt.query(s, s+pos[a]);
			a = parent[root[chain[a]]];
		}
		if (pos[a] != pos[b]) {
			int s = start[chain[a]];
			sum += segt.query(s+pos[b]+1, s+pos[a]);
		}
		return sum;
	}

	void insert_path(int a, int b, int v) {
		//cerr << "insert " << a << " " << b << " " << v << nl;
		while (chain[a] != chain[b]) {
			int s = start[chain[a]];
			segt.insert(s, s+pos[a], v);
			a = parent[root[chain[a]]];
		}
		if (pos[a] != pos[b]) {
			int s = start[chain[a]];
			segt.insert(s + pos[b] + 1, s + pos[a], v);
		}
	}
};

HLD hld;

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
	hld.build(1);

	while (q--) {
		cin >> a >> b >> c >> d;
		// set
		int lca = hld.query(a,b);
		//cerr << "lca: " << lca << nl;
		hld.insert_path(a, lca, 1);
		hld.insert_path(b, lca, 1);
		segt.insert(hld.get(lca), hld.get(lca), 1);
		// query
		int ans = 0;
		int lca2 = hld.query(c,d);
		//cerr << "lca2: " << lca2 << nl;
		ans += segt.query(hld.get(lca2), hld.get(lca2));
		ans += hld.query_path(c, lca2);
		ans += hld.query_path(d, lca2);
		// reset
		hld.insert_path(a, lca, -1);
		hld.insert_path(b, lca, -1);
		segt.insert(hld.get(lca), hld.get(lca), -1);
		// output
		cout << ans << nl;
	}

	return 0;
}
