#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int INF = 0x3f3f3f3f;

namespace Flow {
	const int N = 501*501 + 2;
	struct Edge { int v, r; ll f, c; };
	vector<Edge> adj[N]; int sz[N]; ll mc;
	void init(int n=N) {
		mc = 0;
		fill(sz, sz+n, 0);
		fill(adj, adj+n, vector<Edge>());
	}
	void add_edge(int a, int b, ll c=1) {
		mc = max(mc, c);
		adj[a].push_back({b, sz[b]++, 0, c});
		adj[b].push_back({a, sz[a]++, 0, 0});
	}
	int L[N], cur[N], Q[N];
	bool bfs(int s, int t, ll lim=1) {
		memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
		int f,b; Q[f=b=0] = s; L[s] = 0;
		while(f<=b && L[t]==INF) { int u=Q[f++];
			for(const Edge& e : adj[u]) if (L[e.v]==INF && e.c-e.f >= lim) {
				Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF;
	}
	ll dfs(int u, int t, ll f) { if(u==t || !f) return f;
		for(int i=cur[u]; i<sz[u]; cur[u]=++i) { Edge& e = adj[u][i];
			if (e.f<e.c && L[e.v]==L[u]+1) {
				if(ll cf = dfs(e.v, t, min(e.c-e.f, f))) {
					e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0;
	}
	ll flow(int s, int t, bool sc=0) {
		ll inf=numeric_limits<ll>::max();
		ll res = 0;
		for(ll lim=(sc?mc:1); lim; lim/=2) {
			while(bfs(s,t,lim)) while(ll cf=dfs(s,t,inf)) res += cf;
		}
		return res;
	}
}

vector<int> di = { 0, 0, 1, -1 };
vector<int> dj = { 1, -1, 0, 0 };

const int N = 500 + 2;
char g[N][N];
int mat[N][N], adj[N][N];

int get(int i, int j) {
	return i*501 + j;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	const int SS = 0;
	const int TT = 1;

	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		fill(&g[0][0], &g[0][0]+N*N, ' ');
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				cin >> g[i][j];
				adj[i][j] = 0;
				mat[i][j] = 0;
			}
		}

		bool ok = true;
		queue<pair<int,int>> white;
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				if(g[i][j] == 'B') {
					for(int d=0; d<4; d++) {
						if(g[i+di[d]][j+dj[d]] == 'W') {
							adj[i][j] |= 1<<d;
						}
					}
				} else if(g[i][j] == 'W') {
					for(int d=0; d<4; d++) {
						if(g[i+di[d]][j+dj[d]] == 'B') {
							adj[i][j] |= 1<<d;
						}
					}
					if(adj[i][j] == 0) {
						ok = false;
					} else if(__builtin_popcount(adj[i][j]) == 1) {
						white.push(make_pair(i, j));
						//cerr<<"init push "<<i<<" "<<j<<nl;
					}
				}
			}
		}

		if(!ok) {
			//cerr<<"pre bad"<<nl;
			cout << "NO" << nl;
			continue;
		}

		while(!white.empty()) {
			auto [i, j] = white.front();
			white.pop();
			//cerr<<"visit "<<i<<" "<<j<<" w/ "<<bitset<4>(adj[i][j])<<nl;
			int d = 0;
			for(; d<4; d++) {
				if(adj[i][j] & 1<<d) {
					break;
				}
			}
			if(d == 4) {
				ok = false;
				break;
			}
			assert(adj[i][j] == (1<<d));
			int bi = i + di[d];
			int bj = j + dj[d];

			mat[bi][bj]++;
			int op = ((1<<d & 0b11) ? (1<<d ^ 0b11) : (1<<d ^ 0b1100));
			adj[bi][bj] ^= op;
			adj[i][j] ^= 1<<d;

			int wi = bi + di[d];
			int wj = bj + dj[d];
			if(adj[bi][bj] & 1<<d) {
				adj[bi][bj] ^= 1<<d;
				adj[wi][wj] ^= op;
				if(__builtin_popcount(adj[wi][wj]) == 1) {
					//cerr<<"opp push "<<wi<<" "<<wj<<nl;
					white.push(make_pair(wi, wj));
				}
			}

			if(mat[bi][bj] == 2) {
				for(int e=0; e<4; e++) {
					if(adj[bi][bj] & 1<<e) {
						int ep = ((1<<e & 0b11) ? (1<<e ^ 0b11) : (1<<e ^ 0b1100));
						int ni = i + di[e];
						int nj = j + dj[e];
						adj[bi][bj] ^= 1<<e;
						adj[ni][nj] ^= ep;
						if(__builtin_popcount(adj[ni][nj]) == 1) {
							//cerr<<"done "<<wi<<" "<<wj<<nl;
							white.push(make_pair(ni, nj));
						}
					}
				}
				assert(adj[bi][bj] == 0);
			}
			assert(adj[i][j] == 0);
		}

		if(!ok) {
			cout << "NO" << nl;
			continue;
		}

		Flow::init();
		int wcnt = 0;
		int bcnt = 0;
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				if(g[i][j] == 'B') {
					if(mat[i][j] == 0) {
						ok = false;
					} else if(mat[i][j] == 2) {
						assert(adj[i][j] == 0);
					} else {
						assert(mat[i][j] == 1);
						Flow::add_edge(get(i,j), TT);
						bcnt++;
					}
				} else if(g[i][j] == 'W') {
					if(adj[i][j] > 0) {
						Flow::add_edge(SS, get(i,j));
						wcnt++;
						for(int d=0; d<4; d++) {
							if(adj[i][j] & 1<<d) {
								int ni = i + di[d];
								int nj = j + dj[d];
								assert(g[ni][nj] == 'B');
								Flow::add_edge(get(i,j), get(ni,nj));
							}
						}
					}
				}
			}
		}

		//cerr<<"wcnt: "<<wcnt<<nl;
		//cerr<<"bcnt: "<<bcnt<<nl;
		if(!ok || wcnt != bcnt) {
			//cerr<<"post bad"<<nl;
			cout << "NO" << nl;
			continue;
		}

		if(Flow::flow(SS, TT) == wcnt) {
			cout << "YES" << nl;
		} else {
			cout << "NO" << nl;
		}
	}

}
