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

struct Node {
	int i, d;
	bool operator < (const Node& o) const {
		return d > o.d;
	}
};

const int N = 2e5+1;
vector<int> adj[N], rev[N];
int d[N], c[N], r[N];
int indeg[N], outdeg[N];

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

	for (int i=1; i<=n; i++) {
		cin >> d[i] >> c[i] >> r[i];
		for (int j=0; j<r[i]; j++) {
			int v;
			cin >> v;
			adj[i].push_back(v);
			indeg[v]++;
			rev[v].push_back(i);
			outdeg[i]++;
		}
	}

	// dag dp on adj/in to get minv
	queue<int> topo;
	for (int i=1; i<=n; i++) {
		if (indeg[i] == 0) {
			topo.push(i);
		}
	}
	while (!topo.empty()) {
		int u = topo.front();
		topo.pop();
		for (int v : adj[u]) {
			d[v] = min(d[v],d[u]);
			indeg[v]--;
			if (indeg[v] == 0) {
				topo.push(v);
			}
		}
	}

	// greedy on rev/out to get answer 
	priority_queue<Node> greedy;
	for (int i=1; i<=n; i++) {
		if (outdeg[i] == 0) {
			greedy.push({i,d[i]});
		}
	}
	vector<int> ans;
	while (!greedy.empty()) {
		Node cur = greedy.top();
		greedy.pop();
		ans.push_back(cur.i);
		for (int v : rev[cur.i]) {
			outdeg[v]--;
			if (outdeg[v] == 0) {
				greedy.push({v,d[v]});
			}
		}
	}

	// check size
	if (ans.size() < n) {
		cout << "NO" << nl;
		return 0;
	}

	// check the order
	ll ct = 0;
	for (int it : ans) {
		ct += c[it];
		if (ct > d[it]) {
			cout << "NO" << nl;
			return 0;
		}
	}

	cout << "YES" << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
