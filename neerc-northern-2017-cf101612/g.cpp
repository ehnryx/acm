#include <bits/stdc++.h>
using namespace std;

#define FILENAME "grand"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 1e5+1;
vector<int> adj[N];
unordered_set<int> skip[N];
int par[N], vis[N], cyc[N], depth[N];

void answer(int u, int v, int w, int t) {
	cout << u << " " << t << nl;

	vector<int> path;

	// u -> v -> t
	path.push_back(u);
	for(int i=v; i!=t; i=cyc[i]) {
		path.push_back(i);
	}
	path.push_back(t);
	cout << path.size();
	for(int j : path) {
		cout << " " << j;
	}
	cout << nl;

	// u -> t
	path.clear();
	for(int i=u; i!=t; i=par[i]) {
		path.push_back(i);
	}
	path.push_back(t);
	cout << path.size();
	for(int j : path) {
		cout << " " << j;
	}
	cout << nl;

	// u -> w -> t
	path.clear();
	vector<int> other;
	for(int i=t; i!=w; i=par[i]) {
		other.push_back(i);
	}
	other.push_back(w);
	for(int i=u; i!=w; i=cyc[i]) {
		path.push_back(i);
	}
	reverse(other.begin(), other.end());
	path.insert(path.end(), other.begin(), other.end());
	cout << path.size();
	for(int j : path) {
		cout << " " << j;
	}
	cout << nl;
}

void answer2(int u, int v, int w, int t) {
	cout << u << " " << w << nl;

	vector<int> path;

	// u -> w (cyc)
	for(int i=u; i!=w; i=cyc[i]) {
		path.push_back(i);
	}
	path.push_back(w);
	cout << path.size();
	for(int j : path) {
		cout << " " << j;
	}
	cout << nl;

	// u -> w (par)
	path.clear();
	for(int i=u; i!=w; i=par[i]) {
		path.push_back(i);
	}
	path.push_back(w);
	cout << path.size();
	for(int j : path) {
		cout << " " << j;
	}
	cout << nl;

	// u -> v -> t -> w
	path.clear();
	vector<int> other;
	for(int i=w; i!=t; i=par[i]) {
		other.push_back(i);
	}
	other.push_back(t);
	path.push_back(u);
	for(int i=v; i!=t; i=cyc[i]) {
		path.push_back(i);
	}
	reverse(other.begin(), other.end());
	path.insert(path.end(), other.begin(), other.end());
	cout << path.size();
	for(int j : path) {
		cout << " " << j;
	}
	cout << nl;
}

int decompose(int u, int p) {
	if(vis[u]) {
		skip[u].insert(p);
		return u;
	}
	vis[u] = true;
	par[u] = p;
	depth[u] = depth[p] + 1;
	int wait = 0;
	for(int v : adj[u]) {
		if(v == p || skip[u].count(v)) continue;
		int to = decompose(v, u);
		if(to == -1) return -1;
		if(to && to != u) {
			if(!wait) {
				wait = to;
				cyc[u] = v;
			} else {
				if(depth[wait] <= depth[to]) {
					answer(u, v, wait, to);
				} else {
					answer2(u, v, wait, to);
				}
				return -1;
			}
		}
	}
	return wait;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	if(fopen(FILENAME ".in", "r")) {
		freopen(FILENAME ".in", "r", stdin);
		freopen(FILENAME ".out", "w", stdout);
	}

	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		for(int i=1; i<=n; i++) {
			adj[i].clear();
			skip[i].clear();
			vis[i] = false;
			par[i] = 0;
			cyc[i] = 0;
		}
		for(int i=0; i<m; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		bool done = false;
		for(int i=1; i<=n; i++) {
			if(!vis[i] && decompose(i, 0) == -1) {
				done = true;
				break;
			}
		}
		if(!done) {
			cout << -1 << nl;
		}
	}

	return 0;
}
