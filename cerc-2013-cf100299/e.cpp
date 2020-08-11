#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
	int id, cost, gain;
	Node(int i = -1, int x = 0): id(i) {
		cost = gain = 0;
		if (x > 0) gain = x;
		else cost = -x;
	}
	Node(int i, int c, int g): id(i), cost(c), gain(g) {}
	bool operator < (const Node& n) const {
		return cost > n.cost;
	}
	friend ostream& operator << (ostream& os, const Node& v) {
		return os << v.id << ":(" << v.cost << ',' << v.gain << ")";
	}

	void combine(const Node& child) {
		gain -= child.cost;
		if (gain < 0) {
			cost += abs(gain);
			gain = 0;
		}
		gain += child.gain;
	}
};

const int N = 2e5 + 1;
Node nodes[N];
vector<int> adj[N];
int parent[N];
int degree[N];

void init(int n) {
	fill(nodes, nodes+n, Node());
	fill(adj, adj+n, vector<int>());
	memset(parent, -1, n * sizeof parent[0]);
	memset(degree, 0, n * sizeof degree[0]);
}

void root_tree(int cur, int par = -1) {
	parent[cur] = par;
	for (int x : adj[cur]) {
		if (x != par) {
			root_tree(x, cur);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n, t;
		cin >> n >> t;
		init(n+1);

		int a, b;
		for (int i = 1; i <= n; i++) {
			cin >> a;
			nodes[i] = Node(i, a);
		}
		for (int i = 1; i < n; i++) {
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
			degree[a]++;
			degree[b]++;
		}
		nodes[0] = Node(0, INF);
		adj[t].push_back(0);
		adj[0].push_back(t);
		degree[t]++;
		degree[0]++;
		root_tree(1);

		priority_queue<Node> next;
		degree[1] = INF;
		for (int i = 0; i <= n; i++) {
			if (degree[i] == 1) {
				next.push(nodes[i]);
			}
		}

		while (!next.empty()) {
			Node cur = next.top();
			next.pop();

			cerr << "upd node " << cur << endl;
			int par = parent[cur.id];
			if (cur.gain > cur.cost) {
				nodes[par].combine(cur);
			}
			degree[par]--;
			if (degree[par] == 1) {
				next.push(nodes[par]);
				cerr << "push node " << nodes[par] << endl;
			}
		}
		cerr << "ANS: " << nodes[1].cost << " " << nodes[1].gain << nl;
		cout << (nodes[1].cost == 0 ? "escaped" : "trapped") << nl;
	}

	return 0;
}
