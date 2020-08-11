//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct SegTree {
	static const int N = 1<<20;
	int st[2*N];
	void insert(int x, int v) {
		x += N;
		st[x] = v;
		for(x/=2;x;x/=2) {
			st[x] = min(st[2*x], st[2*x+1]);
		}
	}
	int query(int l, int r) {
		int res = INF;
		for(l+=N, r+=N; l<r; l/=2, r/=2) {
			if(l&1) res = min(res, st[l++]);
			if(r&1) res = min(res, st[--r]);
		}
		return res;
	}
};

const int N = 1e6 + 1;
const int M = 26;
int adj[N][M];
int depth[N], order[N];
int ans[N];
bool add[N];
int dp[N];

SegTree dst, ost;

void build(int u, int& id) {
	id += add[u];
	order[u] = id;
	if(u>0) {
		//cerr<<"@ "<<u<<" w/ order "<<order[u]<<nl;
		dp[u] = dst.query(0, depth[u]) + depth[u];
		//cerr<<"depth -> "<<dst.query(0, depth[u])<<" + "<<depth[u]<<nl;
		if(add[u]) {
			dp[u] = min(dp[u], ost.query(0, depth[u]) + order[u]);
			//cerr<<"order -> "<<ost.query(0, depth[u])<<" + "<<order[u]<<nl;
		}
	}
	dst.insert(depth[u], dp[u] - depth[u]);
	ost.insert(depth[u], dp[u] - order[u] + add[u]);
	//cerr<<"insert depth "<<dp[u]<<" - "<<depth[u]<<nl;
	//cerr<<"insert order "<<dp[u]<<" - "<<order[u]<<" + "<<add[u]<<nl;
	//cerr<<"^ inserted at "<<depth[u]<<nl;
	for(int i=0; i<M; i++) {
		if(!adj[u][i]) continue;
		depth[adj[u][i]] = depth[u] + 1;
		build(adj[u][i], id);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		int p; char c;
		cin >> p >> c;
		adj[p][c-'a'] = i;
	}

	int m;
	cin >> m;
	for(int i=0; i<m; i++) {
		cin >> ans[i];
		add[ans[i]] = true;
	}

	int id = 0;
	build(0, id);

	for(int i=0; i<m; i++) {
		cout << dp[ans[i]] << " ";
	}
	cout << nl;

	return 0;
}
