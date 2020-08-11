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

namespace FruitBorscht {
	const int N = 20;
	int adj[N][N];
	int dp[N][1<<N];

	int solve(int n, int u, int bm) {
		if(dp[u][bm] != -1) return dp[u][bm];
		if(bm == 0) return dp[u][bm] = 0;
		int res = INF;
		for(int v=0; v<n; v++) {
			if(!(bm & 1<<v)) continue;
			res = min(res, adj[u][v] + solve(n, v, bm ^ 1<<v));
		}
		return dp[u][bm] = res;
	}

	int brute_force(int n, int m) {
		memset(adj, INF, sizeof adj);
		for(int i=0; i<m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			adj[a][b] = adj[b][a] = c;
		}

		for(int k=0; k<n; k++) {
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
				}
			}
		}

		memset(dp, -1, sizeof dp);
		int ans = 2*(n-1);
		for(int i=0; i<n; i++) {
			ans = min(ans, solve(n, i, ((1<<n)-1) ^ 1<<i));
		}
		return ans;
	}
}

const int N = 5e5 + 1;
vector<int> adj[N];
int par[N], depth[N];

int val[N];
int path[N][2], dp[N];

void root_tree(int u, int p) {
	par[u] = p;
	depth[u] = depth[p] + 1;
	if(p) adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
	for(int v : adj[u]) {
		root_tree(v, u);
	}
}

int solve(int u) {
	if(dp[u] != -1) return dp[u];
	int res = 0;
	vector<int> first(2, 0), second(2, 0);
	for(int v : adj[u]) {
		res = max(res, solve(v));
		for(int t=0; t<2; t++) {
			if(path[v][t] > first[t]) {
				second[t] = first[t];
				first[t] = path[v][t];
			} else if(path[v][t] > second[t]) {
				second[t] = path[v][t];
			}
		}
	}
	res = max(res, first[0] + second[0]);
	res = max(res, first[0] + second[1]);
	res = max(res, first[1] + second[0]);
	res = max(res, first[1] + second[1]);
	if(val[u] == 1) {
		path[u][0] = first[0] + 1;
		path[u][1] = first[1] + 1;
	} else {
		path[u][0] = 0;
		path[u][1] = max(first[0] + 1, first[1] - 1);
	}
	assert(res >= 0);
	return dp[u] = res;
}

int solve_edge(int n, int a, int b, int c) {
	if(depth[a] < depth[b]) swap(a, b);
	int sub = 0;

	vector<int> changed;
	while(depth[a] > depth[b]) {
		changed.push_back(a);
		dp[a] = -1;
		sub++;
		val[a] = -1;
		a = par[a];
	}
	while(a != b) {
		changed.push_back(a);
		changed.push_back(b);
		dp[a] = dp[b] = -1;
		sub += 2;
		val[a] = val[b] = -1;
		a = par[a];
		b = par[b];
	}
	while(a) {
		changed.push_back(a);
		dp[a] = -1;
		a = par[a];
	}

	int res = 2*(n-1) - sub - solve(1) + c;
	for(int v : changed) {
		val[v] = 1;
		dp[v] = -1;
	}
	return res;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	if(n <= 20) {
		cout << FruitBorscht::brute_force(n, m) << nl;
		return 0;
	}

	vector<tuple<int,int,int>> edges;
	for(int i=0; i<m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		++a; ++b;
		if(c == 1) {
			adj[a].push_back(b);
			adj[b].push_back(a);
		} else {
			edges.emplace_back(a, b, c);
		}
	}
	root_tree(1, 0);

	m = edges.size();
	fill(dp, dp+N, -1);
	fill(val, val+N, 1);
	int ans = solve_edge(n, 1, 1, 0);
	for(int i=0; i<m; i++) {
		auto [a, b, c] = edges[i];
		ans = min(ans, solve_edge(n, a, b, c));
	}
	cout << ans << nl;

	return 0;
}
