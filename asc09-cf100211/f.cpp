//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "restore"

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

const int N = 200 + 1;
int dist[N][N];
vector<int> adj[N*N];
int depth[N*N], par[N*N];

void add_edge(int a, int b) {
	adj[a].push_back(b);
	adj[b].push_back(a);
	par[b] = a;
	depth[b] = depth[a] + 1;
}

void sad() {
	cout << -1 << nl;
	exit(0);
}

int nid;
void add_path(int a, int b, int d) {
	for(int i=depth[a]; i+1<d; i++) {
		if(i == depth[a]) {
			add_edge(a, nid++);
		} else {
			add_edge(nid-1, nid);
			nid++;
		}
	}
	if(depth[a] + 1 == d) {
		add_edge(a, b);
	} else {
		add_edge(nid-1, b);
	}
}

int distance(int a, int b) {
	int res = 0;
	if(depth[a] < depth[b]) swap(a, b);
	while(depth[a] > depth[b]) {
		a = par[a];
		res++;
	}
	while(a != b) {
		res += 2;
		a = par[a];
		b = par[b];
	}
	return res;
}

int get(int a, int d) {
	while(depth[a] != d) {
		a = par[a];
	}
	return a;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
//*/

	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cin >> dist[i][j];
		}
	}
	nid = n + 1;

	add_path(1, 2, dist[1][2]);
	for(int i=3; i<=n; i++) {
		int last = 1;
		for(int j=2; j<i; j++) {
			int c = dist[1][i] + dist[1][j] - dist[i][j];
			if(c % 2 || c/2 >= dist[1][i] || c/2 >= dist[1][j]) sad();
			int lca = get(j, c/2);
			if(depth[lca] > depth[last]) last = lca;
		}
		add_path(last, i, dist[1][i]);
	}

	for(int i=1; i<=n; i++) {
		if(adj[i].size() != 1) sad();
		for(int j=1; j<i; j++) {
			if(distance(i, j) != dist[i][j]) {
				sad();
			}
		}
	}

	cout << nid - 1 << nl;
	for(int i=1; i<nid; i++) {
		for(int j : adj[i]) {
			if(i < j) {
				cout << i << " " << j << nl;
			}
		}
	}

	return 0;
}
