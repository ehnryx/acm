#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

const int INF = 0x3f3f3f3f;

namespace Flow {
	const int N = 3e4;
	struct Edge { int v, r, f, c; };
	vector<Edge> adj[N]; int sz[N];
	vector<pair<int,int>> memo;
	void add_edge(int a, int b, int c=1, bool rem=false) {
		if(rem) memo.emplace_back(a, sz[a]);
		adj[a].push_back({b,sz[b]++,0,c});
		adj[b].push_back({a,sz[a]++,0,0});
	}

	int L[N], cur[N], Q[N];
	bool bfs(int s, int t) {
		memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
		int f,b; Q[f=b=0] = s; L[s] = 0;
		while(f<=b && L[t]==INF) { int u = Q[f++];
			for(const Edge& e : adj[u]) if(L[e.v] == INF && e.f < e.c) {
				Q[++b] = e.v; L[e.v] = L[u] + 1; } } return L[t] < INF;
	}
	int dfs(int u, int t, int f) { if(u==t || !f) return f;
		for(int i=cur[u]; i<sz[u]; cur[u]=++i) { Edge& e = adj[u][i];
			if(e.f < e.c && L[e.v] == L[u]+1) {
				if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
					e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0;
	}
	int flow(int s, int t) { int inf=numeric_limits<int>::max();
		int res = 0;
		while(bfs(s,t)) while(int cf=dfs(s,t,inf)) res += cf;
		return res;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	const int S = n + m + 2*k + 1;
	const int T = S+1;
	const int SS = S+2;
	const int TT = S+3;

	for(int i=1; i<=n; i++) {
		Flow::add_edge(S, i, INF);
		Flow::add_edge(S, TT, 1);
		Flow::add_edge(SS, i, 1);
	}
	for(int i=1; i<=m; i++) {
		Flow::add_edge(n+i, T, INF);
		Flow::add_edge(n+i, TT, 1);
		Flow::add_edge(SS, T, 1);
	}
	Flow::add_edge(T, S, INF);

	map<pair<int,int>,int> lidx, ridx;
	int lid = 0;
	int rid = 0;
	for(int i=1; i<=k; i++) {
		int l, r, t;
		cin >> l >> r >> t;
		pair<int,int> left(l, t);
		pair<int,int> right(r, t);
		if(!lidx.count(left)) {
			lidx[left] = ++lid;
			Flow::add_edge(l, n+m + lid);
		}
		if(!ridx.count(right)) {
			ridx[right] = ++rid;
			Flow::add_edge(n+m+k + rid, n + r);
		}
		Flow::add_edge(n+m + lidx[left], n+m+k + ridx[right], 1, true);
	}

	if(Flow::flow(SS, TT) < n+m) {
		cout << -1 << nl;
	} else {
		vector<int> ans;
		for(int i=1; i<=k; i++) {
			auto [v, e] = Flow::memo[i-1];
			if(Flow::adj[v][e].f > 0) {
				ans.push_back(i);
			}
		}
		cout << ans.size() << nl;
		for(int it : ans) {
			cout << it << " ";
		}
		cout << nl;
	}

	return 0;
}
