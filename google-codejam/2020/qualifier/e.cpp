#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) { os << it << " "; }
	return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
	return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		cout << "Case #" << cc << ": ";
		solve();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

namespace Flow {
	const int N = 100 + 2;
	struct Edge { int v, r; int f, c; };
	vector<Edge> adj[N]; int sz[N];
	void init(int n=N) {
		fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
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
		int res = 0;
		while(bfs(s,t)) {
			while(int cf = dfs(s,t,INF)) {
				res += cf;
			}
		}
		return res;
	}
}

const int N = 50 + 1;
int g[N][N];

void caseinit(int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			g[i][j] = 0;
		}
	}
}

void solve_small(int n, int k) {
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			g[i][j] = 0;
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			g[i][j] = j+1;
		}
		sort(g[i], g[i]+3);
	}

	do {
		do {
			do {
				int trace = 0;
				for(int i=0; i<n; i++) {
					trace += g[i][i];
				}
				if(trace != k) continue;

				set<int> row[n], col[n];
				bool ok = true;
				for(int i=0; i<n; i++) {
					for(int j=0; j<n; j++) {
						ok &= (g[i][j] != 0);
						row[i].insert(g[i][j]);
						col[j].insert(g[i][j]);
					}
				}
				for(int i=0; i<n; i++) {
					ok &= (row[i].size() == n);
					ok &= (col[i].size() == n);
				}

				if(ok) {
					cout << "POSSIBLE" << nl;
					for(int i=0; i<n; i++) {
						for(int j=0; j<n; j++) {
							cout << g[i][j] << " ";
						}
						cout << nl;
					}
					return;
				}
			} while(next_permutation(g[2], g[2]+3));
		} while(next_permutation(g[1], g[1]+3));
	} while(next_permutation(g[0], g[0]+3));

	cout << "IMPOSSIBLE" << nl;
	return;
}

void solve_big(int n) {
	vector<bool> done(n+1);
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			done[g[i][j]] = true;
		}
	}

	const int S = 2*n;
	const int T = S+1;
	for(int v=1; v<=n; v++) {
		if(done[v]) continue;
		Flow::init(2*n + 2);
		for(int i=0; i<n; i++) {
			Flow::add_edge(S, i);
			Flow::add_edge(i+n, T);
			for(int j=0; j<n; j++) {
				if(g[i][j] == 0) {
					Flow::add_edge(i, j+n);
				}
			}
		}
		assert(Flow::flow(S, T) == n);

		for(int i=0; i<n; i++) {
			for(const auto& e : Flow::adj[i]) {
				if(e.v != S && e.f > 0) {
					assert(g[i][e.v-n] == 0);
					g[i][e.v-n] = v;
				}
			}
		}
	}

	//set<int> row[n], col[n];
	cout << "POSSIBLE" << nl;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cout << g[i][j] << " ";
			//row[i].insert(g[i][j]);
			//col[j].insert(g[i][j]);
			//assert(1 <= g[i][j] && g[i][j] <= n);
		}
		cout << nl;
	}

	//for(int i=0; i<n; i++) {
		//assert(row[i].size() == n);
		//assert(col[i].size() == n);
	//}
}

void solve() {

	int n, k;
	cin >> n >> k;
	caseinit(n);

	if(n <= 3) {
		solve_small(n, k);
		return;
	}

	for(int a=1; a<=n; a++) {
		if(a*n == k) {
			for(int i=0; i<n; i++) {
				g[i][i] = a;
			}
			solve_big(n);
			return;
		}

		for(int b=1; b<=n; b++) {
			if(b == a) continue;
			if(a*(n-2) + 2*b == k) {
				g[0][1] = g[1][0] = a;
				g[0][0] = g[1][1] = b;
				for(int i=2; i<n; i++) {
					g[i][i] = a;
					if(i+1<n) g[i][i+1] = b;
					else g[i][2] = b;
				}
				solve_big(n);
				return;
			}

			for(int c=1; c<=n; c++) {
				if(c == b || c == a) continue;
				if(a*(n-2) + b + c == k) {
					g[0][1] = g[1][0] = a;
					g[1][1] = b;
					g[0][0] = c;
					for(int i=2; i<n; i++) {
						g[i][i] = a;
						if(i+1<n) g[i][i+1] = b;
						g[i][i-1] = c;
					}
					g[1][n-1] = c;
					g[0][2] = g[n-1][0] = b;
					solve_big(n);
					return;
				}
			}
		}
	}

	cout << "IMPOSSIBLE" << nl;
	//assert(k < n || k == n+1 || k > n*n || k == n*n-1);

	return;
}

