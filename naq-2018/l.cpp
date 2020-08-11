#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 200+2;
const int M = N*N;

namespace Dinic {
	int par[N], first[N], nxt[2*M], ep[2*M], m;
	ll flo[2*M], cap[2*M], cost[2*M];
	void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
	void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
		nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
		nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
	int L[N], cur[N];
	bool bfs(int s, int t) {
		memset(L, INF, sizeof L);
		queue<int> q; q.push(s); L[s] = 0;
		while (!q.empty()) { int u = q.front(); q.pop();
			for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
				if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
					q.push(v), L[v] = L[u]+1;
		} return L[t] < INF;
	}
	ll dfs(int u, int t, ll f) {
		if (u == t) return f;
		ll cf, df = 0;
		for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
			if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
				cf = dfs(v, t, min(cap[e]-flo[e], f-df));
				flo[e] += cf; flo[e^1] -= cf; df += cf;
			} return df; }
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, k;
	cin >> n >> k;

	int grid[n][n];
	set<int> rows[n], cols[n];
	for (int i=0; i<k; i++) {
		for (int j=0; j<n; j++) {
			cin >> grid[i][j];
			rows[i].insert(grid[i][j]);
			cols[j].insert(grid[i][j]);
		}
		if (rows[i].size() < n) {
			cout << "no" << nl;
			return 0;
		}
	}
	for (int j=0; j<n; j++) {
		if (cols[j].size() < k) {
			cout << "no" << nl;
			return 0;
		}
	}

	const int source = 0;
	const int sink = n+n+1;
	for (int i=k; i<n; i++) {
		Dinic::init();
		for (int j=0; j<n; j++) {
			Dinic::add_edge(n+1+j, sink);
			for (int v=1; v<=n; v++) {
				if (!cols[j].count(v)) {
					Dinic::add_edge(v, n+1+j);
				}
			}
		}
		for (int v=1; v<=n; v++) {
			Dinic::add_edge(source, v);
		}

		int flow = 0;
		while (Dinic::bfs(source, sink)) {
			flow += Dinic::dfs(source, sink, INF);
		}
		assert(flow == n);

		for (int v=1; v<=n; v++) {
			for (int e=Dinic::first[v]; e!=-1; e=Dinic::nxt[e]) {
				if (Dinic::flo[e] > 0 && Dinic::ep[e^1] != source) {
					int u = Dinic::ep[e^1]-n-1;
					grid[i][u] = v;
					assert(!cols[u].count(v));
					cols[u].insert(v);
				}
			}
		}
	}

	cout << "yes" << nl;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			assert(grid[i][j]);
			cout << grid[i][j] << ' ';
		}
		cout << nl;
	}

	return 0;
}
