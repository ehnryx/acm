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

struct Edge {
	int a, b, c;
	bool operator < (Edge& o) const {
		return c < o.c;
	}
};

vector<Edge> all, other;
struct DSU {
	int groups;
	vector<int> root;
	void init(int n) {
		groups = n;
		root.clear();
		root.resize(n,-1);
	}
	int find(int i) {
		if (root[i] == -1) return i;
		return root[i] = find(root[i]);
	}
	int link(int i, int j) {
		if (find(i) == find(j)) return false;
		root[find(i)] = find(j);
		groups--;
		return true;
	}
};
DSU dsu;

const int L = 19;
const int N = 1<<L;
int idx[N], answer[N];
int maxe;
vector<int> adj[N];
DSU ndsu[N];

void UPDATE(int, int, int);

////////////////////////////////////////////////////////////////////////
// Range Minimum Query -- O(nlogn) to build, O(1) to query
// Query range is inclusive
// Code is probably not very safe
//*!
template<class T> struct RMQ {
  T rmq[2*N][L+1]; int lg[2*N];
  void build(int n) { for (int j=1; j<2*n; j++) lg[j]=31-__builtin_clz(j);
    for (int j=1; j<L+1; j++) for (int i=0; i+(1<<j)-1<2*n; i++)
      rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]); }
  T query(int a, int b) { if (a>b) swap(a,b);
    int j=lg[b-a+1]; return min(rmq[a][j], rmq[b-(1<<j)+1][j]); }
};
//*/

////////////////////////////////////////////////////////////////////////
// Lowest Common Ancestor -- Using RMQ
// Nodes are 1-indexed
//*!
struct LCA : RMQ<pii> {
  int dh[N], sp[N];
  int par[N], subsz[N]; // These are for HLD
  int lcan; LCA() { lcan = dh[0] = 0; }
	void init() { lcan = dh[0] = 0; }
  void build(int root, int n) { build_lca(root,0); RMQ::build(n); }
  int build_lca(int cur, int p) {
    dh[cur] = dh[par[cur]=p]+1; sp[cur] = lcan; subsz[cur] = 1;
    rmq[lcan++][0] = pii(dh[cur],cur);
    for (int i:adj[cur]) if (i!=p) { subsz[cur] += build_lca(i,cur);
      rmq[lcan++][0]=pii(dh[cur],cur); } return subsz[cur]; }
  int query(int a, int b) { return RMQ::query(sp[a],sp[b]).second; }
};
//*/

////////////////////////////////////////////////////////////////////////
// Heavy Light Decomposition -- O(n) to build
// TESTED ON cf1023/f
// * Nodes are 1-indexed
//*!
struct HLD : LCA {
  vector<int> sz, root, start; // indexed by chains
  int chain[N], pos[N]; // indexed by nodes
  int hldn, segn; HLD(): LCA() { hldn = segn = 0; }
	void init() { hldn = segn = 0; LCA::init();
		sz.clear(); root.clear(); start.clear();
	}
  int get(int i) const { return start[chain[i]] + pos[i]; } // position
  void build(int r, int n) { LCA::build(r,n); build_hld(r,0); }
  void build_hld(int cur, int p) {
    if (hldn == root.size()) {
      root.push_back(cur); start.push_back(segn); sz.push_back(0);
    } chain[cur] = hldn; pos[cur] = sz[chain[cur]]++; segn++;
    int best=-1, child=-1;
    for (int x:adj[cur])
      if (x!=p && subsz[x]>best) { best = subsz[child=x]; }
    if (child != -1) build_hld(child, cur);
    for (int x:adj[cur])
      if (x!=p && x!=child) { hldn++; build_hld(x,cur); } }
  // Inserting a path into a segtree on the chains
  // insert_path interval is [a,b), but UPDATE is [s,t]
  // path: a -> b, b is an ancestor of a
  int insert_path(int a, int b, int v, int ignore) {
		int ret = -1;
    while (chain[a] != chain[b]) {
      int s = start[chain[a]];
			if (par[root[chain[a]]] == ignore) {
				UPDATE(s+1, s+pos[a], v);
				ret = s;
			} else {
				UPDATE(s, s+pos[a], v); // update segtree here
			}
      a = par[root[chain[a]]];
    }
    if (pos[a] != pos[b]) {
      int s = start[chain[a]];
      UPDATE(s+pos[b]+2, s+pos[a], v); // update segtree here
			ret = s+pos[b]+1;
    }
		return ret;
  }
};
//*/

HLD hld;

set<int> bit;
unordered_map<int,int> nidx[N];

void DO_THE_THING(int x, int a, int b, int c) {
	//cerr << "DO THE THING " << x << " " << a << " " << b << " " << c << nl;
	if (ndsu[x].link(nidx[x][a], nidx[x][b]) && ndsu[x].groups == 1) {
		answer[x] = c;
		//cerr << "!!" << nl;
	}
}

void UPDATE(int a, int b, int v) {
	if (a>b) return;
	//cerr << "UPDATE " << a << " " << b << nl;
	for (auto it = bit.lower_bound(a); it != bit.end() && (*it) <= b; it = bit.erase(it)) {
		int x = idx[*it];
		int p = hld.par[x];
		int pp = hld.par[p];
		DO_THE_THING(p, x, pp, v);
	}
}

void init(int n) {
	all.clear();
	other.clear();
	dsu.init(n+1);
	bit.clear();
	bit.insert(0);
	for (int i=1; i<=n; i++) {
		bit.insert(i);
		adj[i].clear();
		answer[i] = -1;
	}
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

	int n, m;
	for (int tt=1; cin>>n>>m; tt++) {
		//cerr << nl << nl;
		init(n);
		int a, b, c;
		for (int i=0; i<m; i++) {
			cin >> a >> b >> c;
			all.push_back({a,b,c});
		}
		sort(all.begin(), all.end());

		for (const Edge& e : all) {
			if (dsu.link(e.a, e.b)) {
				adj[e.a].push_back(e.b);
				adj[e.b].push_back(e.a);
				maxe = e.c;
			} else {
				other.push_back(e);
			}
		}

		if (dsu.groups > 2) {
			goto wtf;
		}

		for (int i=1; i<=n; i++) {
			nidx[i].clear();
			ndsu[i].init(adj[i].size());
			int cnt = 0;
			for (int j : adj[i]) {
				nidx[i][j] = cnt++;
			}
			if (ndsu[i].groups == 1) {
				answer[i] = maxe;
			}
		}

		hld.init();
		hld.build(1,n+1);
		for (int i=1; i<=n; i++) {
			idx[hld.get(i)] = i;
		}

		for (const Edge& e : other) {
			int lca = hld.query(e.a, e.b);
			int x = hld.insert_path(e.a, lca, e.c, lca);
			int y = hld.insert_path(e.b, lca, e.c, lca);
			if (e.a==lca || e.b==lca) continue;
			//cerr << x << " -> " << idx[x] << nl;
			//cerr << y << " -> " << idx[y] << nl;
			x = idx[x];
			y = idx[y];
			DO_THE_THING(lca, x, y, e.c);
		}

wtf:
		cout << "Case " << tt << ":";
		for (int i=1; i<=n; i++) {
			if (answer[i] != -1) answer[i] = max(answer[i], maxe);
			cout << " " << answer[i];
		}
		cout << nl;
	}

	return 0;
}
