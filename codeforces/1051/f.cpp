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
	int pre, id;
	ll dist;
	Edge(int p, int i, ll d): pre(p), id(i), dist(d) {}
};

const int N = 1e5+1;
const int L = 18;

int root[N];
int find(int i) {
	if (root[i] == -1) return i;
	return root[i] = find(root[i]);
}
bool link(int i, int j) { 
	if (find(i) != find(j)) {
		root[find(i)] = find(j);
		return true;
	}
	return false;
}

vector<Edge> adj[N];
int depth[N], segpos[N];
ll len[N];
pii rmq[2*N][L+1];

int query_rmq(int l, int r) {
	if (l>r) swap(l,r);
	int j = 31-__builtin_clz(r-l+1);
	return min(rmq[l][j], rmq[r-(1<<j)+1][j]).second;
}

void build_rmq(int n) {
	n *= 2;
	for (int j=1; j<=L; j++) {
		for (int i=0; i+(1<<j)-1<n; i++) {
			rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
		}
	}
}

int lcanum = 0;
void build(int cur, int par, ll dist) {
	depth[cur] = depth[par]+1;
	len[cur] = len[par]+dist;
	segpos[cur] = lcanum;
	rmq[lcanum++][0] = pii(depth[cur],cur);
	for (const Edge& e : adj[cur]) {
		if (e.id != par) {
			build(e.id, cur, e.dist);
			rmq[lcanum++][0] = pii(depth[cur],cur);
		}
	}
}

ll query(int a, int b) {
	int c = query_rmq(segpos[a],segpos[b]);
	return len[a]+len[b]-2*len[c];
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

	memset(root, -1, sizeof root);

	int n, m, a, b, c;
	cin >> n >> m;

	vector<Edge> edges;
	for (int i=0; i<m; i++) {
		cin >> a >> b >> c;
		edges.push_back(Edge(a,b,c));
	}

	unordered_set<int> seen;
	vector<Edge> cross;
	for (const Edge& e : edges) {
		if (link(e.pre, e.id)) {
			adj[e.pre].push_back(Edge(e.pre, e.id, e.dist));
			adj[e.id].push_back(Edge(e.id, e.pre, e.dist));
		} else {
			cross.push_back(e);
			seen.insert(e.pre);
			seen.insert(e.id);
		}
	}
	build(1, 0, 0);
	build_rmq(n);

	vector<int> node;
	unordered_map<int,int> nid;
	for (int i : seen) {
		nid[i] = node.size();
		node.push_back(i);
	}
	m = node.size();

	ll trivial[m][m];
	memset(trivial, INF, sizeof trivial);
	for (const Edge& e : cross) {
		trivial[nid[e.pre]][nid[e.id]] = trivial[nid[e.id]][nid[e.pre]] = e.dist;
	}
	for (int i=0; i<m; i++) {
		for (int j=0; j<m; j++) {
			trivial[i][j] = min(trivial[i][j], query(node[i],node[j]));
		}
	}
	for (int k=0; k<m; k++) {
		for (int i=0; i<m; i++) {
			for (int j=0; j<m; j++) {
				trivial[i][j] = min(trivial[i][j], trivial[i][k]+trivial[k][j]);
			}
		}
	}

	int q;
	cin >> q;
	while (q--) {
		cin >> a >> b;
		ll ans = query(a, b);
		for (int i=0; i<m; i++) {
			for (int j=0; j<m; j++) {
				ans = min(ans, query(a,node[i])+query(b,node[j])+trivial[i][j]);
			}
		}
		cout << ans << nl;
	}

	return 0;
}
