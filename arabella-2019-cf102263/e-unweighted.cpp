#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
	int i, c;
};

struct Query {
	int a, b, c;
};

const int N = 2e5+1;
vector<Edge> adj[N];
int par[N];
int dp1[N], bestd[N], sec[N], secd[N], third[N], dp2[N], up1[N], up2[N];

int path_down(int u, int p = -1) {
	if (dp1[u] != -1) return dp1[u];
	if (p != -1) par[u] = p;
	int res = 0;
	for (const Edge& e : adj[u]) {
		if (e.i != par[u]) {
			int path = 1 + path_down(e.i, u);
			if (path > res) {
				secd[u] = bestd[u];
				sec[u] = res;
				bestd[u] = e.i;
				res = path;
			} else if (path > sec[u]) {
				third[u] = sec[u];
				secd[u] = e.i;
				sec[u] = path;
			} else {
				third[u] = max(third[u], path);
			}
		}
	}
	return dp1[u] = res;
}

int solve_down(int u) {
	if (dp2[u] != -1) return dp2[u];
	int res = dp1[u] + sec[u];
	for (const Edge& e : adj[u]) {
		if (e.i != par[u]) {
			res = max(res, solve_down(e.i));
		}
	}
	return dp2[u] = res;
}

int path_up(int u) {
	if (up1[u] != -1) return up1[u];
	int res = -INF;
	if (par[u]) {
		res = max(res, 1 + path_up(par[u]));
		if (bestd[par[u]] == u) {
			res = max(res, 1 + sec[par[u]]);
		} else {
			res = max(res, 1 + dp1[par[u]]);
		}
	}
	up1[u] = res;
	for (const Edge& e : adj[u]) {
		if (e.i != par[u]) {
			path_up(e.i);
		}
	}
	return up1[u];
}

int solve_up(int u) {
	if (up2[u] != -1) return up2[u];
	int res = -INF;
	if (par[u]) {
		res = max(res, solve_up(par[u]));
		// up
		if (bestd[par[u]] == u) {
			res = max(res, path_up(par[u]) + sec[par[u]]);
		} else {
			res = max(res, path_up(par[u]) + dp1[par[u]]);
		}
		// down
		if (bestd[par[u]] == u) {
			res = max(res, sec[par[u]] + third[par[u]]);
		} else if (secd[par[u]] == u) {
			res = max(res, dp1[par[u]] + third[par[u]]);
		} else {
			res = max(res, dp1[par[u]] + sec[par[u]]);
		}
	}
	up2[u] = res;
	for (const Edge& e : adj[u]) {
		if (e.i != par[u]) {
			solve_up(e.i);
		}
	}
	return up2[u];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	memset(dp1, -1, sizeof dp1);
	memset(dp2, -1, sizeof dp2);
	memset(up1, -1, sizeof up1);
	memset(up2, -1, sizeof up2);

	int n;
	cin >> n;

	vector<Query> edges;
	For(i,n-1) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
		edges.push_back({a,b,c});
	}
	path_down(1, 0);
	solve_down(1);
	path_up(1);
	solve_up(1);

#define DEBUG
#ifdef DEBUG
	FOR(i,1,n) {
		cerr << i << ": " << path_down(i) << " " << solve_down(i) << " " << path_up(i) << " " << solve_up(i) << nl;
	}
#endif

	for (const Query& it : edges) {
		int a = it.a;
		int b = it.b;
		if (a == par[b]) swap(a,b);
		int dlen = solve_down(a);
		int ulen = solve_up(a);
		cout << max((dlen+1)/2 + 1 + (ulen+1)/2, max(dlen, ulen)) << nl;
	}

	return 0;
}
