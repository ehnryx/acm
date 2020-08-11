#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

const char nl = '\n';
const int INF = 0x3f3f3f3f;

namespace Flow {
	const int N = 2e5+7;
	struct Edge { int v, r; int f, c; };
	vector<Edge> adj[N]; int sz[N];
	void add_edge(int a, int b, int c=1) {
		adj[a].push_back({b,sz[b]++,0,c});
		adj[b].push_back({a,sz[a]++,0,0}); }
	int L[N], cur[N], Q[N];
	bool bfs(int s, int t) {
		memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
		int f,b; Q[f=b=0] = s; L[s] = 0;
		while(f<=b && L[t]==INF) { int u = Q[f++];
			for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c > e.f) {
				Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
	int dfs(int u, int t, int f) { if (u == t || !f) return f;
		for (int i = cur[u]; i < sz[u]; cur[u] = ++i) { Edge& e = adj[u][i];
			if(e.f<e.c && L[e.v]==L[u]+1) {
				if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
					e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0; }
	int flow(int s, int t) {
		int inf=numeric_limits<int>::max();
		int res = 0;
		while(bfs(s,t)) {
			while(int cf=dfs(s,t,inf)) {
				res += cf;
			}
		}
		return res;
	}
}

const int N = 1e5+1;
vector<pair<int,int>> tree[N];
unordered_map<int,int> ans[N];

int solve(int u, int cap) {
	int done = 0;
	for(auto [s, v] : tree[u]) {
		int up = solve(v, cap);
		ans[s][v] = cap - 1 - up;
		ans[s][u] = up + 1;
		done += up + 1;
	}
	assert(0 <= done && done < cap);
	return done;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	const int S = 0;
	const int T = 2*n + 1;
	vector<pair<int,int>> edges;
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		Flow::add_edge(a, b+n);
		edges.push_back(make_pair(a,b));
	}
	for(int i=1; i<=n; i++) {
		if(i<n) Flow::add_edge(S, i);
		Flow::add_edge(i+n, T);
	}

	int num = Flow::flow(S, T);
	if(num < n-1) {
		cout << -1 << nl;
		return 0;
	}

	vector<int> mat(n+1);
	vector<bool> seen(n+1);
	for(int i=1; i<n; i++) {
		for(const auto& e : Flow::adj[i]) {
			if(e.v > n && e.f) {
				assert(!mat[i] && !seen[e.v-n]);
				mat[i] = e.v - n;
				seen[e.v - n] = true;
			}
		}
	}

	int root = 0;
	for(int i=1; i<=n; i++) {
		if(!seen[i]) {
			assert(!root);
			root = i;
		}
	}

	vector<bool> used(n+1);
	stack<int> dfs;
	dfs.push(root);
	int tot = 0;
	while(!dfs.empty()) {
		int u = dfs.top();
		dfs.pop();
		tot++;
		for(const auto& e : Flow::adj[u+n]) {
			if(e.v < n && !used[e.v]) {
				used[e.v] = true;
				dfs.push(mat[e.v]);
				tree[u].push_back(make_pair(e.v, mat[e.v]));
			}
		}
	}

	if(tot < n) {
		cout << -1 << nl;
		return 0;
	}

	solve(root, n);

	for(auto [a, b] : edges) {
		cout << ans[a][b] << nl;
	}

	return 0;
}
