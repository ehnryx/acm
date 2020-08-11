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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace SAT {
	const int N = 52*52 * 2;
	int low[N],vis[N],scomp[N],scompNum,I;
	vector<int> adj[N]; stack<int> verts;
	void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
		for (int v : adj[u]) {
			if (!vis[v]) scc(v);
			if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
		if (vis[u] <= low[u]) { int v;
			do { v=verts.top(); verts.pop(); scomp[v]=scompNum; } while (v != u);
			++scompNum; }}
	void get_scc(int n) { memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
		scompNum=I=0; for (int i=0; i<n; ++i) if (!vis[i]) scc(i); }
	bool truth[N/2]; // N must be at least 2 times the number of variables
	void add_clause(int a, int b) { adj[a].push_back(b); }
	bool two_sat(int n=N) { get_scc(n);
		for (int i = 0; i < n; i += 2) { if (scomp[i] == scomp[i^1]) return false;
			truth[i/2] = (scomp[i] < scomp[i^1]); } return true; }
}

const int N = 52;
char g[N][N];
vector<int> adj[N*N];
vector<bool> vis[N*N];

void visit(int s) {
	vis[s].resize(N*N, false);
	vis[s][s] = true;
	stack<int> dfs;
	dfs.push(s);
	while(!dfs.empty()) {
		int u = dfs.top();
		dfs.pop();
		for(int v:adj[u]) {
			if(!vis[s][v]) {
				vis[s][v] = true;
				dfs.push(v);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	function<int(int,int)> get = [&](int i, int j) {
		return i*(m+2) + j;
	};
	function<int(int)> F = [](int i) {
		return 2*i + 1;
	};
	function<int(int)> T = [](int i) {
		return 2*i;
	};

	fill(&g[0][0], &g[0][0]+N*N, '#');
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin >> g[i][j];
		}
	}

	int s = -1;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(g[i][j] == '#') continue;
			int u = get(i,j);
			for(int k=i; k>=1; k--) {
				if(g[k-1][j] == '#') {
					adj[u].push_back(get(k,j));
					break;
				}
			}
			for(int k=i; k<=n; k++) {
				if(g[k+1][j] == '#') {
					adj[u].push_back(get(k,j));
					break;
				}
			}
			for(int k=j; k>=1; k--) {
				if(g[i][k-1] == '#') {
					adj[u].push_back(get(i,k));
					break;
				}
			}
			for(int k=j; k<=m; k++) {
				if(g[i][k+1] == '#') {
					adj[u].push_back(get(i,k));
					break;
				}
			}
			if(g[i][j] == 'O') {
				s = u;
				SAT::add_clause(F(u), T(u));
			} else if(g[i][j] == '*') {
				SAT::add_clause(F(adj[u].front()), T(adj[u].back()));
				SAT::add_clause(F(adj[u].back()), T(adj[u].front()));
			}
		}
	}
	assert(s != -1);

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			visit(get(i,j));
		}
	}

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			int u = get(i,j);
			if(!vis[s][u]) {
				SAT::add_clause(T(u), F(u));
			} else {
				for(int ii=1; ii<=n; ii++) {
					for(int jj=1; jj<=m; jj++) {
						int v = get(ii,jj);
						if(!vis[u][v] && !vis[v][u]) {
							SAT::add_clause(T(u), F(v));
							SAT::add_clause(T(v), F(u));
						}
					}
				}
			}
		}
	}

	if(SAT::two_sat()) {
		cout << "YES" << nl;
	} else {
		cout << "NO" << nl;
	}

	return 0;
}
