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
	const int N = 800 + 7;
	struct Edge { int v, r, f, c; };
	vector<Edge> adj[N]; int sz[N];
	void clear_flow() {
		for(int i=0; i<N; i++) {
			for(Edge& e : adj[i]) {
				e.f = 0;
			}
		}
	}
	void add_edge(int a, int b, int c) {
		adj[a].push_back({b, sz[b]++, 0, c});
		adj[b].push_back({a, sz[a]++, 0, c});
	}
	int L[N], cur[N], Q[N];
	bool bfs(int s, int t) {
		memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
		int f,b; Q[f=b=0] = s; L[s] = 0;
		while(f <= b && L[t] == INF) { int u = Q[f++];
			for(const Edge& e : adj[u]) if (L[e.v] == INF && e.f < e.c) {
				Q[++b] = e.v; L[e.v] = L[u] + 1; } } return L[t] < INF;
	}
	int dfs(int u, int t, int f) { if (u == t || !f) return f;
		for(int i=cur[u]; i<sz[u]; cur[u]=++i) { Edge& e = adj[u][i];
			if(e.f < e.c && L[e.v] == L[u] + 1) {
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
		while(bfs(s,t)) while(int cf=dfs(s,t,inf)) res += cf;
		return res;
	}
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

#ifdef ONLINE_JUDGE
	freopen("attack.in", "r", stdin);
	freopen("attack.out", "w", stdout);
#endif

	int n, m, s, t;
	cin >> n >> m >> s >> t;

	for(int i=0; i<m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		Flow::add_edge(a, b, c);
	}
	Flow::flow(s, t);

	vector<int> first;
	for(int i=1; i<=n; i++) {
		if(Flow::L[i] < INF) first.push_back(i);
	}
	sort(first.begin(), first.end());

	Flow::clear_flow();
	Flow::flow(t, s);
	vector<int> second;
	for(int i=1; i<=n; i++) {
		if(Flow::L[i] == INF) second.push_back(i);
	}
	sort(second.begin(), second.end());

	if(first == second) {
		cout << "UNIQUE" << nl;
	} else {
		cout << "AMBIGUOUS" << nl;
	}

	return 0;
}
