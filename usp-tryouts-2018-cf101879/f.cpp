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
	int id, pre, dist, cur;
	Edge(){}
	Edge(int i, int d): id(i), dist(d) {}
	Edge(int i, int p, int d, int c): id(i), pre(p), dist(d), cur(c) {}
	bool operator < (const Edge& e) const {
		return dist > e.dist;
	}
};

const int N = 1e5+1;
const int M = 5e5+1;
vector<Edge> adj[N];
vector<Edge> rev[N], other[N];
Edge pre[N];
int dist[N], tot[N], path[N];
int vis[N];

void dijkstra(int s, int t) {
	memset(dist, -1, sizeof dist);
	priority_queue<Edge> nxt;

	nxt.push(Edge(s,0,0,0));
	while (!nxt.empty()) {
		Edge cur = nxt.top();
		nxt.pop();

		if (dist[cur.id] == -1) {
			// update distance
			dist[cur.id] = cur.dist;
			if (cur.id != t) {
				for (const Edge& e : adj[cur.id]) {
					nxt.push(Edge(e.id, cur.id, e.dist + cur.dist, e.dist));
				}
			}
			// update tree
			pre[cur.id] = Edge(cur.pre, cur.cur);
			rev[cur.pre].push_back(Edge(cur.id, cur.cur));
		}
		else {
			// update cross edges
			other[cur.id].push_back(Edge(cur.pre, cur.cur));
		}
	}
}

int toposort(int t) {
	if (dist[t] == -1) {
		//cerr << "Why is this -1 ??" << nl;
		return -1;
	}

	memset(path, -1, sizeof path);
	memset(tot, INF, sizeof tot);
	map<int,unordered_set<int>> route;

	int res = dist[t];
	tot[t] = 0;
	for (int cur = t; pre[cur].id != 0; cur = pre[cur].id) {
		// update tot in unvisited subtree
		priority_queue<Edge> upd;
		stack<int> dfs;

		dfs.push(cur);
		while (!dfs.empty()) {
			int i = dfs.top();
			dfs.pop();
			upd.push(Edge(i, tot[i]));
			vis[i] = -1;
			for (const Edge& e : rev[i]) {
				if (!vis[e.id]) {
					tot[e.id] = min(tot[e.id], e.dist + tot[i]);
					dfs.push(e.id);
				}
			}
		}

		// multi-source dijkstra to update cross edges
		while (!upd.empty()) {
			Edge temp = upd.top();
			int i = temp.id;
			upd.pop();

			// update distance to t
			if (vis[i] == -1) {
				if (path[i] != -1) {
					//cerr << "REMOVE route through " << i << " w/ dist " << path[i] << nl;
					route[path[i]].erase(i);
					if (route[path[i]].empty()) route.erase(path[i]);
				}
				vis[i] = true;
				//cerr << "update tot @ " << i << " from " << tot[i] << " w/ " << temp.dist << nl;
				tot[i] = min(tot[i], temp.dist);
				for (const Edge& e : other[i]) {
					if (vis[e.id] != true) {
						upd.push(Edge(e.id, e.dist + tot[i]));
					}
				}
			}

			// update route through unvisited node
			else if (!vis[i]) {
				if (path[i] != -1) {
					//cerr << "REMOVE route through " << i << " w/ dist " << path[i] << nl;
					route[path[i]].erase(i);
					if (route[path[i]].empty()) route.erase(path[i]);
				}
				tot[i] = min(tot[i], temp.dist);
				route[dist[i]+tot[i]].insert(i);
				path[i] = dist[i]+tot[i];
				//cerr << "ADD route through " << i << " w/ dist " << dist[i]+tot[i] << nl;
			}
		}

		// update parent
		tot[pre[cur].id] = min(tot[pre[cur].id], pre[cur].dist + tot[cur]);

		// try removing edge to pre
		//cerr << "try removing " << pre[cur].id << "->" << cur << nl;
		if (route.empty()) {
			//cerr << "  disconnected !!!" << nl;
			return -1;
		} else {
			//cerr << "  res updated from " << res << " with " << route.begin()->first << nl;
			res = max(res, route.begin()->first);
		}
	}

	return res;
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

	int n, m, s, t, a, b, c;

	cin >> n >> m;
	cin >> s >> t;

	if (s == t) {
		//cerr << "what the hell?" << endl;
		cout << 0 << nl;
		return 0;
	}

	for (int i=0; i<m; i++) {
		cin >> a >> b >> c;
		adj[a].push_back(Edge(b,c));
		adj[b].push_back(Edge(a,c));
	}
	dijkstra(s,t);
	cout << toposort(t) << nl;

	return 0;
}
