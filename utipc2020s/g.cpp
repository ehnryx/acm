#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

const ll INF = 0x3f3f3f3f;

namespace Flow {
	const int N = 1e2 + 7;
	struct Edge {int v, r; ll f, c; };
	vector<Edge> adj[N]; int sz[N];
	void add_edge(int a, int b, ll c=1) {
		adj[a].push_back({b, sz[b]++, 0, c});
		adj[b].push_back({a, sz[a]++, 0, 0});
	}
	int L[N], cur[N], Q[N];
	bool bfs(int s, int t, ll lim=1) {
		memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
		int f,b; Q[f=b=0] = s; L[s] = 0;
		while(f <= b && L[t] == INF) { int u = Q[f++];
			for(const Edge& e : adj[u]) if(L[e.v] == INF && e.c-e.f >= lim) {
				Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF;
	}
	ll dfs(int u, int t, ll f) { if(u == t || !f) return f;
		for(int i=cur[u]; i<sz[u]; cur[u]=++i) { Edge& e = adj[u][i];
			if(e.f < e.c && L[e.v] == L[u] + 1) {
				if(ll cf = dfs(e.v, t, min(e.c-e.f, f))) {
					e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0;
	}
	ll flow(int s, int t, bool scaling=0) {
		ll inf = numeric_limits<ll>::max();
		ll res = 0;
		for(ll lim=(scaling?1<<17:1); lim; lim/=2) {
			while(bfs(s,t,lim)) while(ll cf=dfs(s,t,inf)) res += cf;
		}
		return res;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	const int BIG = 1e5 + 1;

	int n;
	cin >> n;
	ll init = 0;
	const int S = 0;
	const int T = n+1;
	for(int i=1; i<=n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		init += a - BIG;
		Flow::add_edge(S, i, BIG - b);
		Flow::add_edge(i, T, BIG - c);
	}

	int m;
	cin >> m;
	for(int i=0; i<m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		Flow::add_edge(a, b, c);
		Flow::add_edge(b, a, c);
	}
	ll flow = Flow::flow(S, T);
	cout << init + flow << nl;

	return 0;
}
