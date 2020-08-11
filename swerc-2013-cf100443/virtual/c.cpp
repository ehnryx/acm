#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int N = 205;
const ld INF = 1e18;

#define nl '\n'

struct pt {
	ld x, y, z;
	pt operator-(const pt& o) const {
		return pt{x-o.x, y-o.y, z-o.z};
	}
};
ld abs(const pt& p) {
	return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}

pt pts[N];
ld dist[N][N];
int par[N];
bool vis[N];
ld d[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> pts[i].z >> pts[i].x >> pts[i].y;
		pts[i].z *= 5;
	}
	for (int i = 0; i < N; i++) {
		fill(dist[i], dist[i] + N, INF);
		dist[i][i] = 0;
	}
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		string s; cin >> s;
		if (s[0] == 'w' || s[0] == 's') {
			dist[u][v] = dist[v][u] = abs(pts[v]-pts[u]);
		} else if (s[0] == 'l') {
			dist[u][v] = dist[v][u] = 1;
		} else {
			dist[u][v] = 1;
			dist[v][u] = 3*abs(pts[v]-pts[u]);
		}
	}
	int q; cin >> q;
	while (q--) {
		int a, b; cin >> a >> b;
		priority_queue<pair<ld, int>> pq;
		pq.emplace(0, a);
		memset(par, -1, sizeof par);
		fill(d, d + N, INF);
		d[a] = 0;
		memset(vis, 0, sizeof vis);
		while (!pq.empty()) {
			int cur; tie(ignore, cur) = pq.top(); pq.pop();
			if (vis[cur]) continue;
			if (cur == b) break;
			vis[cur] = 1;
			for (int i = 0; i < n; i++) {
				if (!vis[i] && d[i] > d[cur] + dist[cur][i]) {
					d[i] = d[cur] + dist[cur][i];
					par[i] = cur;
					pq.emplace(-d[i], i);
				}
			}
		}
		vector<int> ans;
		int cur = b;
		while (cur != -1) {
			ans.push_back(cur);
			cur = par[cur];
		}
		reverse(ans.begin(), ans.end());
		for (int i : ans) {
			cout << i << " ";
		}
		cout << nl;
	}

	return 0;
}
