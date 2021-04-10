#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const char nl = '\n';
const int INF = 0x3f3f3f3f;

struct Edge {
	int id, dist, i;
	bool operator < (const Edge& o) const {
		return dist > o.dist;
	}
};

struct Cross {
	int a, b, c, i;
};

const int N = 1e4;
int dist[N], par[N];
vector<Edge> adj[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case #" << tt << ": ";

		int m;
		cin >> m;

		int pid = 0;
		map<pii,int> points;
		vector<Cross> edges;
		for (int i=0; i<m; i++) {
			int x1, y1, x2, y2, w;
			cin >> x1 >> y1 >> x2 >> y2 >> w;
			pii a(x1,y1);
			pii b(x2,y2);
			if (!points.count(a)) {
				adj[pid].clear();
				points[a] = pid++;
			}
			if (!points.count(b)) {
				adj[pid].clear();
				points[b] = pid++;
			}
			adj[points[a]].push_back({points[b],w,i});
			adj[points[b]].push_back({points[a],w,i});
			edges.push_back({points[a],points[b],w,i});
		}

		int ans = INF;
		for (int s=0; s<pid; s++) {
			if (adj[s].size() == 1) continue;
			memset(dist, INF, pid*sizeof(int));
			memset(par, -1, pid*sizeof(int));
			dist[s] = 0;
			queue<int> dijk;
			dijk.push(s);
			while (!dijk.empty()) {
				int cur = dijk.front();
				dijk.pop();
				for (const Edge& e : adj[cur]) {
					int nd = e.dist + dist[cur];
					if (nd < dist[e.id]) {
						dist[e.id] = nd;
						par[e.id] = e.i;
						dijk.push(e.id);
					}
				}
			}
			for (const Cross& e : edges) {
				if (dist[e.a] == INF || e.i == par[e.b] || e.i == par[e.a]) continue;
				ans = min(ans, dist[e.a]+dist[e.b]+e.c);
			}
		}

		if (ans == INF) {
			cout << 0 << nl;
		} else {
			cout << ans << nl;
		}
	}

	return 0;
}
