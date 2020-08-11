#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

namespace FLOW {

const int N = 100 + 100 + 2;
const int M = 100*100 + 100 + 100;

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

double sqr(double x) {
	return x*x;
}

int main() {
	freopen("wall.in", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int source = 100 + 100;
	int sink = source + 1;

	int grid[100][100];

	int T;
	cin >> T;
	while (T--) {
		memset(grid, 0, sizeof(grid));
		int n, m, p;
		double x, y;
		cin >> n >> m >> p;
		for (int r = 0; r < p; r++) {
			cin >> x >> y;
			int i = x;
			int j = y - sqrt(sqr(n/2.0) - sqr(x-n/2.0));
			grid[i][j] = 1;
		}

		FLOW::init();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] > 0) {
					FLOW::add_edge(i, 100+j, 1);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			FLOW::add_edge(source, i, 1);
		}
		for (int j = 0; j < m; j++) {
			FLOW::add_edge(100+j, sink, 1);
		}

		ll flow = 0;
		while (FLOW::bfs(source, sink))
			flow += FLOW::dfs(source, sink, INF);
		cout << flow << nl;
	}

	return 0;
}
