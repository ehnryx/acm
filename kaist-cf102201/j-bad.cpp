//#pragma GCC optimize("O3")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
template <typename T> inline void read(T &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

namespace Flow {
	const int N = 2e5 + 1;
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
	ll flow(int s, int t) {
		ll res = 0;
		while(clock()<2.8*CLOCKS_PER_SEC && bfs(s,t)) {
			while(int cf=dfs(s,t,INF)) res += cf;
		}
		return res;
	}
}

struct Edge {
	int v, e;
};

const int N = 1e5+1;
unordered_map<int,int> cost[N];
int have[N], need[N];
vector<pii> ADJ[N];
vector<Edge> st[N];
int deg[N], stdeg[N];

int dsu[N];
int find(int i) {
	if(dsu[i] == -1) return i;
	return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
	if(find(i) != find(j)) {
		dsu[find(i)] = find(j);
	}
}

int main() {
	int n, m;
	read(n); read(m);
	const int S = 0;
	const int T = n;
	vector<int> adj[n];
	vector<pii> edges;
	for(int i=0; i<m; i++) {
		int a, b;
		read(a); read(b);
		Flow::add_edge(a, n+b, n-1);
		adj[a].push_back(i);
		edges.push_back(make_pair(a,b));
		ADJ[a].push_back(make_pair(0,b));
		deg[b]++;
	}
	for(int i=1; i<=n; i++) {
		Flow::add_edge(n+i, T, n-1);
		if(i<n) Flow::add_edge(S, i, n);
	}
	ll res = Flow::flow(S, T);
	if(res != (ll)n*(n-1)) {

		memset(dsu, -1, sizeof dsu);

		for(int i=1; i<n; i++) {
			for(auto& it : ADJ[i]) {
				it.first = deg[it.second];
			}
			sort(ADJ[i].begin(), ADJ[i].end());

			int u = ADJ[i][0].second;
			bool ok = false;
			for(int j=(int)ADJ[i].size()-1; j>0; j--) {
				int v = ADJ[i][j].second;
				if(find(u) != find(v)) {
					st[u].push_back({v,i});
					st[v].push_back({u,i});
					stdeg[u]++;
					stdeg[v]++;
					link(u, v);
					ok = true;
					break;
				}
			}
			if(!ok) {
				cout << -1 << nl;
				return 0;
			}

			for(const auto& it : ADJ[i]) {
				deg[it.second]--;
			}
		}

		queue<int> bfs;
		for(int i=1; i<=n; i++) {
			if(stdeg[i] == 1) {
				bfs.push(i);
			}
			need[i] = n-1;
			if(i<n) have[i] = n;
		}

		while(!bfs.empty()) {
			int u = bfs.front();
			bfs.pop();
			for(auto [v, e] : st[u]) {
				if(have[e] > 0) {
					int move = min(have[e], need[u]);
					have[e] -= move;
					need[u] -= move;
					cost[e][u] += move;
				}
				if(have[e] > 0) {
					int move = min(have[e], need[v]);
					have[e] -= move;
					need[v] -= move;
					cost[e][v] += move;
				}
				stdeg[v]--;
				if(stdeg[v] == 1) {
					bfs.push(v);
				}
			}
		}

		ll tot = 0;
		for(auto [a,b] : edges) {
			tot += cost[a][b];
			cout << cost[a][b] << nl;
		}
		assert(tot == (ll)n*(n-1));

	} else {
		int ans[m];
		for(int i=1; i<n; i++) {
			for(int j=0; j<adj[i].size(); j++) {
				ans[adj[i][j]] = Flow::adj[i][j].f;
			}
		}
		for(int i=0; i<m; i++) {
			cout << ans[i] << nl;
		}
	}

	return 0;
}
