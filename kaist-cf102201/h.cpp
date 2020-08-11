#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Line {
	int m, b;
	ll eval(int x) const {
		return (b == -1 ? INFLL : (ll)m*x + b);
	}
};

const int N = 1<<30;
const int M = 8e4+1;
const int D = 3e7;

int root[M];
Line st[D];
int ls[D], rs[D];

int sid;
void init() {
	sid = 0;
	st[0] = {0, -1};
}

void fix(int& ver, int old, Line v, int l, int r) {
	ver = ++sid;
	ls[ver] = ls[old];
	rs[ver] = rs[old];
	st[ver] = st[old];

	int m = (l+r)/2;
	bool left = (v.eval(l) < st[old].eval(l));
	bool right = (v.eval(r) < st[old].eval(r));
	bool mid = (v.eval(m) < st[old].eval(m));
	if(left == right) {
		if(left) st[ver] = v;
		return;
	}

	if(mid) swap(v, st[ver]);
	fix(ls[ver], ls[old], v, l, m);
	fix(rs[ver], rs[old], v, m+1, r);
}

void insert(int& ver, int old, Line v, int l, int r, int s, int e) {
	if(r<s || e<l) return;
	if(l<=s && e<=r) {
		fix(ver, old, v, s, e);
		return;
	}

	ver = ++sid;
	ls[ver] = ls[old];
	rs[ver] = rs[old];
	st[ver] = st[old];

	int m = (s+e)/2;
	insert(ls[ver], ls[old], v, l, r, s, m);
	insert(rs[ver], rs[old], v, l, r, m+1, e);
}

ll query(int ver, int x, int s, int e) {
	ll res = st[ver].eval(x);
	if(s == e) return res;
	int m = (s+e)/2;
	if(x <= m) return min(res, query(ls[ver], x, s, m));
	else return min(res, query(rs[ver], x, m+1, e));
}

int A[M], B[M], C[M];
vector<int> adj[M];

void build(int u, int p) {
	insert(root[u], root[p], {B[u], A[u]}, 0, C[u], 0, N-1);
	for(int v : adj[u]) {
		if(v == p) continue;
		build(v, u);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	init();

	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) cin >> A[i];
	for(int i=1; i<=n; i++) cin >> B[i];
	for(int i=1; i<=n; i++) cin >> C[i];
	for(int i=1; i<n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	build(1, 0);

	for(int i=0; i<m; i++) {
		int v, t;
		cin >> v >> t;
		cout << query(root[v], t, 0, N-1) << nl;
	}
	assert(sid < D);

	return 0;
}
