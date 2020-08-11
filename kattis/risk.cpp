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

namespace Dinic {
	const int N = 100*2+2;
	const int M = N*N;
	int par[N], first[N], nxt[2*M], ep[2*M], m;
	ll flo[2*M], cap[2*M];
	void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
	void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
		nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, ++m;
		nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, ++m;
	}
	int L[N], cur[N];
	bool bfs(int s, int t) {
		memset(L, INF, sizeof L);
		queue<int> q; q.push(s); L[s] = 0;
		while (!q.empty()) { int u = q.front(); q.pop();
			for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
				if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
					q.push(v), L[v] = L[u]+1;
		} return L[t] < INF; }
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

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		int val[n];
		vector<int> adj[n];
		for (int i=0; i<n; i++) {
			cin >> val[i];
		}
		char t;
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				cin >> t;
				if (t=='Y') adj[i].push_back(j);
			}
		}

		const int source = 2*n;
		const int sink = source+1;

		auto valid = [&] (int lb) {
			Dinic::init();
			int cnt = 0;
			int other = 0;
			for (int i=0; i<n; i++) {
				if (val[i]>0) {
					bool border = false;
					Dinic::add_edge(source, 2*i, val[i]);
					Dinic::add_edge(2*i, 2*i+1, INF);
					for (int j : adj[i]) {
						if (val[j]) {
							Dinic::add_edge(2*i, 2*j+1, INF);
						} else {
							border = true;
						}
					}
					if (border) {
						cnt++;
						Dinic::add_edge(2*i+1, sink, lb);
					} else {
						other++;
						Dinic::add_edge(2*i+1, sink, 1);
					}
				}
			}
			int flow = 0;
			while (Dinic::bfs(source, sink)) {
				flow += Dinic::dfs(source, sink, INF);
			}
			return flow == lb*cnt + other;
		};

		int left = 0;
		int right = n*100;
		while (left<right) {
			int mid = (left+right+1)/2;
			if (valid(mid)) {
				left = mid;
			} else {
				right = mid-1;
			}
		}
		cout << left << nl;
	}

	return 0;
}
