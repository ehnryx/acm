//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
	const int N = 2e4 + 7;
	struct Edge { int v, r, f, c; };
	vector<Edge> adj[N]; int sz[N];
	void init(int n=N) {
		fill(sz, sz+n, 0); fill(adj, adj+n, vector<Edge>());
	}
	void add_edge(int a, int b, int c=1) {
		adj[a].push_back({b, sz[b]++, 0, c});
		adj[b].push_back({a, sz[a]++, 0, 0});
	}

	int L[N], cur[N], Q[N];
	bool bfs(int s, int t) {
		memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
		int f,b; Q[f=b=0] = s; L[s] = 0;
		while(f<=b && L[t]==INF) {
			int u = Q[f++];
			for(const Edge& e : adj[u]) if(L[e.v] == INF && e.f < e.c) {
				Q[++b] = e.v; L[e.v] = L[u]+1;
			}
		}
		return L[t] < INF;
	}
	int dfs(int u, int t, int f) {
		if(u == t || !f) return f;
		for(int i=cur[u]; i<sz[u]; cur[u]=++i) {
			Edge& e = adj[u][i];
			if(e.f < e.c && L[e.v] == L[u]+1) {
				if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
					e.f += cf; adj[e.v][e.r].f -= cf; return cf;
				}
			}
		}
		return 0;
	}
	int flow(int s, int t) {
		int inf = numeric_limits<int>::max();
		int res = 0;
		while(bfs(s, t)) while(int cf=dfs(s,t,inf)) res += cf;
		return res;
	}
}

const int N = 100 + 2;
int g[N][N], row[N][N], col[N][N];

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while(T--) {
		Flow::init();

		int r, c;
		cin >> r >> c;
		for(int i=1; i<=r; i++) {
			for(int j=1; j<=c; j++) {
				g[i][j] = 0;
			}
		}

		int n;
		cin >> n;
		for(int i=0; i<n; i++) {
			int x, y;
			cin >> x >> y;
			g[x][y] = 1;
		}

		int m;
		cin >> m;
		for(int i=0; i<m; i++) {
			int x, y;
			cin >> x >> y;
			g[x][y] = -1;
		}

		int rid = 1;
		for(int i=1; i<=r; i++) {
			int pre = -1;
			for(int j=1; j<=c; j++) {
				if(g[i][j] == -1) pre = -1;
				if(g[i][j] == 0) continue;
				if(pre == -1) Flow::add_edge(0, ++rid);
				row[i][j] = rid;
				pre = j;
			}
		}

		for(int j=1; j<=c; j++) {
			int pre = -1;
			for(int i=1; i<=r; i++) {
				if(g[i][j] == -1) pre = -1;
				if(g[i][j] == 0) continue;
				if(pre == -1) Flow::add_edge(++rid, 1);
				col[i][j] = rid;
				pre = i;
			}
		}

		for(int i=1; i<=r; i++) {
			for(int j=1; j<=c; j++) {
				if(g[i][j] == 1) {
					Flow::add_edge(row[i][j], col[i][j]);
				}
			}
		}
		cout << Flow::flow(0, 1) << nl;
	}

	return 0;
}
