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

const int N = 1e3;

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
  scompNum=I=0; for (int i=0; i<n; ++i) if (!vis[i]) scc(i); 
}

unordered_set<int> graph[N], rev[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	cin >> n;

	vector<pii> edges;
	vector<int> seen;
	for (int i = 0; i < n; i++) {
		int id, m, v;
		cin >> id >> m;
		seen.push_back(id);
		for (int j = 0; j < m; j++) {
			cin >> v;
			adj[id].push_back(v);
			edges.push_back(pii(id,v));
		}
	}
	get_scc(N);

	for (const pii& e : edges) {
		if (scomp[e.first] != scomp[e.second]) {
			graph[scomp[e.first]].insert(scomp[e.second]);
			rev[scomp[e.second]].insert(scomp[e.first]);
		}
	}

	unordered_set<int> reachable, nottrapped;
	queue<int> bfs;

	bfs.push(scomp[0]);
	reachable.insert(scomp[0]);
	while (!bfs.empty()) {
		int i = bfs.front();
		bfs.pop();
		for (int x : graph[i]) {
			if (!reachable.count(x)) {
				bfs.push(x);
				reachable.insert(x);
			}
		}
	}

	bfs.push(scomp[0]);
	nottrapped.insert(scomp[0]);
	while (!bfs.empty()) {
		int i = bfs.front();
		bfs.pop();
		for (int x : rev[i]) {
			if (!nottrapped.count(x)) {
				bfs.push(x);
				nottrapped.insert(x);
			}
		}
	}

	bool good = true;

	for (int i : seen) {
		if (!nottrapped.count(scomp[i])) {
			cout << "TRAPPED " << i << nl;
			good = false;
		}
	}

	for (int i : seen) {
		if (!reachable.count(scomp[i])) {
			cout << "UNREACHABLE " << i << nl;
			good = false;
		}
	}

	if (good) {
		cout << "NO PROBLEMS" << nl;
	}

	return 0;
}
