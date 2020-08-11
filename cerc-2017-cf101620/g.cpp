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
	int id;
	ld x;
	Node() {}
	Node(int i, ld x): id(i), x(x) {}
	bool operator < (const Node& n) const { return x > n.x; }
};

const int N = 300000 + 1;
vector<int> adj[N];
bool vis[N];
int deg[N];
int nfix[N];
ld nsum[N];
ld ans[N];

void init() {
	memset(vis, 0, sizeof vis);
	memset(deg, 0, sizeof deg);
	memset(nfix, 0, sizeof nfix);
	fill(nsum, nsum+N, 0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int n, m;
	cin >> n >> m;

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
		deg[a]++;
		deg[b]++;
	}

	priority_queue<Node> nxt;
	nxt.push(Node(n, 0));
	while (!nxt.empty()) {
		Node cur = nxt.top();
		nxt.pop();
		if (vis[cur.id]) continue;
		vis[cur.id] = true;
		ans[cur.id] = cur.x;

		for (int nb : adj[cur.id]) {
			if (!vis[nb]) {
				nfix[nb]++;
				nsum[nb] += cur.x;
				nxt.push(Node(nb, nsum[nb]/nfix[nb] + (ld)deg[nb]/nfix[nb]));
			}
		}
	}

	cout << ans[1] << nl;

	return 0;
}
