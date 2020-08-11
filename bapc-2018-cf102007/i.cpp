#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Dinic {
	const int N = (1<<10)+10+2;
	const int M = (1<<10)*10+N;
	int par[N], first[N], nxt[2*M], ep[2*M], m;
	ll flo[2*M], cap[2*M], cost[2*M];
	void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
	void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
		nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
		nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
	// Dinic's fast maximum flow: tested on NAIPC 2015 F but not theoretically
	// proven to be floating-point-safe.
	// USAGE: 1) init(); 2) add edges
	// 3) ll flow=0; while (bfs(S, T)) flow += dfs(S, T, INF);
	// V^2E in general, min(V^(2/3),sqrt(E))E on unit caps, sqrt(V)E on bipartite
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

struct Edge {
	int i; ll d;
	bool operator < (const Edge& o) const {
		return d > o.d;
	}
};

const int N = 1e5+1;
const int M = 10+1;
int p[N];
int s[M], cap[M];
ll gcap[1<<M];
vector<Edge> adj[N];
ll dist[M][N];
bool vis[M][N];
unordered_set<int> reach[M];

void dijkstra(int id) {
	priority_queue<Edge> dijk;
	dijk.push({s[id],0});
	dist[id][s[id]] = 0;
	while (!dijk.empty()) {
		Edge cur = dijk.top();
		dijk.pop();
		if (!vis[id][cur.i]) {
			vis[id][cur.i] = true;
			for (const Edge& e : adj[cur.i]) {
				if (!vis[id][e.i] && e.d+cur.d < dist[id][e.i]) {
					dist[id][e.i] = e.d+cur.d;
					dijk.push({e.i, e.d+cur.d});
				}
			}
		}
	}
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

	int n, m, k;
	cin >> n >> m >> k;

	ll sum = 0;
	FOR(i,1,n) {
		cin >> p[i];
		sum += p[i];
	}

	For(i,m) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}

	memset(dist, INF, sizeof dist);
	For(i,k) {
		cin >> s[i] >> cap[i];
		dijkstra(i);
	}

	const int S = k+(1<<k);
	const int T = k+(1<<k)+1;
	function<bool(ll)> valid = [&] (ll t) {
		memset(gcap, 0, sizeof gcap);
		FOR(i,1,n) {
			int bm = 0;
			For(j,k) {
				if (dist[j][i] <= t) {
					bm |= 1<<j;
				}
			}
			gcap[bm] += p[i];
		}

		Dinic::init();
		For(j,k) {
			Dinic::add_edge(S, j, cap[j]);
			For(bm,1<<k) {
				if (bm&1<<j) {
					Dinic::add_edge(j, k+bm, INF);
				}
			}
		}
		For(bm,1<<k) {
			Dinic::add_edge(k+bm, T, gcap[bm]);
		}

		ll flow = 0;
		while (Dinic::bfs(S,T)) {
			flow += Dinic::dfs(S,T,INFLL);
		}
		return (flow == sum);
	};

	ll left = 0;
	ll right = 1e14;
	while (left < right) {
		ll mid = (left+right)/2;
		if (valid(mid)) {
			right = mid;
		} else {
			left = mid+1;
		}
	}
	cout << left << nl;

	return 0;
}
