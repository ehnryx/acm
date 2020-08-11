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

struct Edge {
	int id, dist;
	bool operator < (const Edge& o) const {
		return dist > o.dist;
	}
};

const int N = 1e3+1;
vector<Edge> adj[N];
int ans[N], dist[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	const int s = 2;
	const int t = 1;

	for (int n,m; cin>>n>>m; ) {
		for (int i=1; i<=n; i++) {
			adj[i].clear();
			dist[i] = INF;
			ans[i] = 0;
		}
		for (int i=0; i<m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			adj[a].push_back({b,c});
			adj[b].push_back({a,c});
		}

		priority_queue<Edge> dijk;
		dijk.push({s,0});
		ans[s] = 1;
		while (!dijk.empty()) {
			Edge cur = dijk.top(); dijk.pop();
			if (dist[cur.id] == INF) {
				dist[cur.id] = cur.dist;
				for (const Edge& e : adj[cur.id]) {
					if (dist[e.id] < cur.dist) {
						ans[cur.id] += ans[e.id];
					} else {
						dijk.push({e.id, e.dist+cur.dist});
					}
				}
			}
		}

		cout << ans[t] << nl;
	}

	return 0;
}
