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
	int id, d;
	Node(int i=INF, int d=INF): id(i), d(d) {}
	bool operator < (const Node& o) const {
		return d > o.d;
	}
};

const int N = 1e6+1;
const int S = 1<<20;
const int L = 20;
vector<int> adj[N];
int depth[N];
int parent[N];

int anc[N][L];
Node rmq[N];
int spos[N], slast[N];

void update(int x, Node v) {
	rmq[x+S] = v;
	for (x += S; x > 1; x >>= 1) {
		rmq[x>>1] = max(rmq[x], rmq[x^1]);
	}
}

int query(int l, int r) {
	Node res;
	for (l+=S, r+=S; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = max(res, rmq[l++]);
		if (r&1) res = max(res, rmq[--r]);
	}
	return res.id;
}

priority_queue<Node> todo;

int sid = 0;
void dfs(int cur, int d = 0) {
	depth[cur] = d;
	spos[cur] = sid++;
	anc[cur][0] = parent[cur];
	for (int i=1; 1<<i<=d; i++) {
		anc[cur][i] = anc[anc[cur][i-1]][i-1];
	}
	if (adj[cur].empty()) {
		todo.push(Node(cur, d));
		update(spos[cur], Node(cur, d));
	}
	for (int x : adj[cur]) {
		dfs(x, d+1);
	}
	slast[cur] = sid;
}

int jump(int cur, int k) {
	k = min(k, depth[cur]);
	for (int i=0; i<L; i++) {
		if (1<<i&k) cur = anc[cur][i];
	}
	return cur;
}

int lca(int a, int b) {
	return query(spos[a], spos[b]);
	int l = spos[root] + S;
	int r = slast[root] + S;

int memo[N];

int solve(int root, int k) {
	int res = 0;
	while (!todo.empty()) {
		if (lca(nxt, root) == root) {
			todo.pop();
			cerr << "try to visit " << nxt << " from " << root << nl;
			res = max(res, 1 + solve(jump(nxt,k), k));
		}
	}
	cerr << "root: " << root << " -> " << res << nl;
	return memo[root] = res; 
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

	int n, k;
	cin >> n >> k;

	for (int i=2; i<=n; i++) {
		cin >> parent[i];
		adj[parent[i]].push_back(i);
	}
	dfs(1);

	cerr << lg[6] << " " << lg[8] << " " << lg[9] << nl;

	memset(memo, -1, sizeof memo);
	cout << solve(1, k) << nl;

	return 0;
}
