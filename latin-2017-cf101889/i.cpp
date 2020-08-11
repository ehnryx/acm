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
	Edge(int a, int b, int c): a(a), b(b), c(c) {}
	bool operator < (const Edge& e) const {
		return c < e.c;
	}
};

////////////////////////////////////////////////////////////////////////
// Disjoint Set Union -- O(a(n)) per query, (inverse ackermann)
// Usage: 
// 1. dsu(n) to create n disjoint sets from 0 to n-1
// 2. dsu.link(i,j) to combine sets containing i and j
// 3. dsu.find(i) to find the root of the set containing i
//*!
struct DSU {
	vector<int> root;
	vector<int> sz;

	DSU(int n) {
		root.resize(n, -1);
		sz.resize(n, 1);
	}

	int find(int i) {
		if (root[i] == -1) return i;
		return root[i] = find(root[i]);
	}

	// returns true if we combine two sets
	bool link(int i, int j) {
		i = find(i);
		j = find(j);
		if (i == j) return false;
		if (sz[i] < sz[j]) swap(i,j);
		root[j] = i;
		sz[i] += sz[j];
		return true;
	}
};
//*/

const int N = 1e5+1;
vector<int> adj[N];
unordered_map<int,int> cost[N];

////////////////////////////////////////////////////////////////////////
// Range Minimum Query -- O(nlogn) to build, O(1) to query
// Maximum query is also possible
// The code is 0-indexed, change the loops in build to make it 1-indexed
// Query range is inclusive
// USAGE:
//  1. RMQ rmq(n);
//  2. rmq.build(vector containing the values);
//  3. rmq.query(l,r);  // range inclusive [l,r]
//*!
template <class T> struct RMQ {
    int lg;
    vector<vector<T>> rmq;

    RMQ(int n) {
        lg = 32 - __builtin_clz(n);
        rmq.resize(n, vector<T>(lg));
    }

    void set(int i, const T& v) {
        rmq[i][0] = v;
    }
    void build() {
        for (int j = 1; j < lg; j++)
            for (int i = 0; i+(1<<j)-1 < rmq.size(); i++)
                rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
    }

    T query(int l, int r) {
        if (l > r) swap(l, r);
        int j = 31 - __builtin_clz(r-l+1);
        return min(rmq[l][j], rmq[r-(1<<j)+1][j]);
    }
};
//*/

////////////////////////////////////////////////////////////////////////
// Lowest Common Ancestor -- Using RMQ
// Nodes are 1-indexed
// USAGE:
//  1. LCA lca(numNodes);
//  2. lca.build(root);
//  3. lca.query(u,v);
//*!
struct LCA : RMQ<pii> {
    vector<int> depth, segpos;
    vector<int> parent, subsz; // These are for HLD
    int lcanum = 0;

    LCA(int n): RMQ<pii>(2*n) {
        lcanum = 0;
        depth.resize(n);
        segpos.resize(n);
        parent.resize(n); // for HLD
        subsz.resize(n); // for HLD
        depth[0] = 0;
    }

    void build(int root) {
        build(root, 0);
        RMQ::build();
    }

    int build(int cur, int par) {
        depth[cur] = depth[par] + 1;
        segpos[cur] = lcanum;
        parent[cur] = par; // for HLD
        subsz[cur] = 1; // for HLD
        RMQ::rmq[lcanum++][0] = pii(depth[cur], cur);
        for (int x : adj[cur]) {
            if (x != par) {
                subsz[cur] += build(x, cur);
                RMQ::rmq[lcanum++][0] = pii(depth[cur], cur);
            }
        }
        return subsz[cur];
    }

    // returns the index, use .first to return the depth
    // could also return (depth,index) by returning a pii
    int query(int a, int b) {
        return RMQ::query(segpos[a],segpos[b]).second;
    }
};
//*/

////////////////////////////////////////////////////////////////////////
// Heavy Light Decomposition -- O(n) to build
// TESTED ON cf1023/f
// Paths on the tree go through O(log(n)) chains
// * Nodes are 1-indexed
// USAGE:
//  1. HLD hld(numNodes);
//  2. hld.build(root)
//  3. look at insert_path for update/query example, we need lca
//*!
struct HLD : LCA {
    vector<int> sz, root, start; // indexed by chains
    vector<int> chain, pos; // indexed by nodes
    int hldnum, segnum;

    HLD(int n): LCA(n) {
        hldnum = segnum = 0;
        chain.resize(n);
        pos.resize(n);
    }

    // 0 indexed, returns the position
    int get(int i) const {
        return start[chain[i]] + pos[i];
    }

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

        int best = -1;
        int child = -1;
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
};
//*/

struct Int {
	int x;
	Int(int x=0): x(x) {}
	bool operator < (const Int& v) const {
		return x > v.x;
	}
};

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, r, a, b, c;
	cin >> n >> r;

	vector<Edge> edges;
	for (int i=0; i<r; i++) {
		cin >> a >> b >> c;
		edges.push_back(Edge(a,b,c));
	}
	sort(edges.begin(), edges.end());

	int sum = 0;
	DSU dsu(n+1);
	for (const Edge& e : edges) {
		if (dsu.link(e.a, e.b)) {
			adj[e.a].push_back(e.b);
			adj[e.b].push_back(e.a);
			sum += e.c;
		}
		cost[e.a][e.b] = e.c;
		cost[e.b][e.a] = e.c;
	}

	HLD hld(n+1);
	hld.build(1);

	RMQ<Int> rmq(n+1);
	for (int i=2; i<=n; i++) {
		rmq.set(hld.get(i), Int(cost[i][hld.parent[i]]));
	}
	rmq.build();

	auto query_path = [&] (int a, int b) {
		int res = 0;
		while (hld.chain[a] != hld.chain[b]) {
			int s = hld.start[hld.chain[a]];
			res = max(res, rmq.query(s, s + hld.pos[a]).x);
			a = hld.parent[hld.root[hld.chain[a]]];
		}
		if (hld.pos[a] != hld.pos[b]) {
			int s = hld.start[hld.chain[a]];
			res = max(res, rmq.query(s + hld.pos[b] + 1, s + hld.pos[a]).x);
		}
		return res;
	};

	int q;
	cin >> q;
	for (int i=0; i<q; i++) {
		cin >> a >> b;
		int lca = hld.query(a,b);
		int maxv = max(query_path(a, lca), query_path(b, lca));
		cout << sum + cost[a][b] - maxv << nl;
	}

	return 0;
}
