#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#pragma GCC Optimize("O3")

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
	Edge(){}
	Edge(int a, int b, int c): a(a), b(b), c(c) {}
	bool operator < (const Edge& v) const {
		return c < v.c;
	}
};

const int N = 1<<19;
const int L = 20;
vector<int> adj[N];

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
DSU dsu(5e5+1);

int segt[2*N];

void hld_update(int l, int r, int v) {
	for (l += N, r += N+1; l < r; l /= 2, r /= 2) {
		if (l&1) {
			segt[l] = min(segt[l], v);
			l++;
		}
		if (r&1) {
			--r;
			segt[r] = min(segt[r], v);
		}
	}
}

int hld_query(int x) {
	int res = INF;
	for (x += N; x > 0; x /= 2) {
		res = min(res, segt[x]);
	}
	return res;
}

void UPDATE(int l, int r, int v) { hld_update(l, r, v); }

////////////////////////////////////////////////////////////////////////
// Range Minimum Query -- O(nlogn) to build, O(1) to query
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

    void build(const vector<T>& a) {
        for (int i = 0; i < a.size(); i++)
            rmq[i][0] = a[i];
        build();
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
// Paths on the tree go through O(log(n)) heavy chains
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

    // Inserting a path into a segtree on the chains
    // insert_path interval is [a,b), but UPDATE is [s,t]
    // path: a -> b, b is an ancestor of a
    // value: v
    void insert_path(int a, int b, int v) {
        while (chain[a] != chain[b]) {
            int s = start[chain[a]];
            UPDATE(s, s + pos[a], v); // update segtree here
            a = parent[root[chain[a]]];
        }
        if (pos[a] != pos[b]) {
            int s = start[chain[a]];
            UPDATE(s + pos[b] + 1, s + pos[a], v); // update segtree here
        }
    }
};
//*/

HLD hld(5e5+1);

namespace std {
	template<> struct hash<pii> {
		size_t operator () (const pii& v) const {
			return hash<int>()(v.first) ^ hash<int>()(v.second<<11);
		}
	};
}
unordered_set<pii> orig;

ll answer(int cur) {
	ll res = 0;
	if (orig.count(pii(cur, hld.parent[cur]))) {
		int v = hld_query(hld.get(cur));
		if (v == INF) return -1;
		res += v;
	}

	for (int x : adj[cur]) {
		if (x != hld.parent[cur]) {
			ll v = answer(x);
			if (v == -1) return -1;
			res += v;
		}
	}
	return res;
}

void init() {
	memset(segt, INF, sizeof segt);
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
	init();

	int n, k, m, a, b, c;
	cin >> n >> k >> m;

	int root = -1;
	int groups = n;
	for (int i = 0; i < k; i++) {
		cin >> a >> b;
		root = a;
		adj[a].push_back(b);
		adj[b].push_back(a);
		orig.insert(pii(a,b));
		orig.insert(pii(b,a));
		groups -= dsu.link(a,b);
	}

	vector<Edge> edges;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		edges.push_back(Edge(a,b,c));
	}
	sort(edges.begin(), edges.end());

	for (const Edge& e : edges) {
		if (groups == 1) break;
		if (dsu.link(e.a, e.b)) {
			adj[e.a].push_back(e.b);
			adj[e.b].push_back(e.a);
			groups--;
		}
	}
	hld.build(root);

	for (const Edge& e : edges) {
		int anc = hld.query(e.a, e.b);
		hld.insert_path(e.a, anc, e.c);
		hld.insert_path(e.b, anc, e.c);
	}

	cout << answer(root) << nl;

	return 0;
}
