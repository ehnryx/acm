//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<17;
int val[N];
vector<int> adj[N];

ll mst[2*N], sst[2*N];

void insert(int x, int v) {
	x += N;
	mst[x] = sst[x] = v;
	for(x/=2;x;x/=2) {
		mst[x] = max(mst[2*x], mst[2*x+1]);
		sst[x] = sst[2*x] + sst[2*x+1];
	}
}

ll query_sum(int l, int r) {
	ll res = 0;
	for(l+=N, r+=N; l<r; l/=2, r/=2) {
		if(l&1) res += sst[l++];
		if(r&1) res += sst[--r];
	}
	return res;
}

ll query_max(int l, int r) {
	ll res = -INFLL;
	for(l+=N, r+=N; l<r; l/=2, r/=2) {
		if(l&1) res = max(res, mst[l++]);
		if(r&1) res = max(res, mst[--r]);
	}
	return res;
}

int start[N], sz[N];
int sid = 0;

int build(int u, int p) {
	start[u] = sid++;
	sz[u] = 1;
	for(int v : adj[u]) {
		if(v == p) continue;
		sz[u] += build(v, u);
	}
	return sz[u];
}

vector<tuple<int,int,int>> queries[N];
ll ans[N];
ordered_set<pair<ll,int>> maxtree, sumtree;
int uid = N;

void solve(int u, int p) {
	for(auto [t, k, i] : queries[u]) {
		if(t == 1) {
			ans[i] = sumtree.find_by_order(k-1)->first;
		} else {
			ans[i] = maxtree.find_by_order(k-1)->first;
		}
	}

	for(int v : adj[u]) {
		if(v == p) continue;
		ll oldsum = query_sum(start[v], start[v] + sz[v]);
		ll oldmax = query_max(start[v], start[v] + sz[v]);
		ll newsum = query_sum(0, start[v]) + query_sum(start[v] + sz[v], sz[1]);
		ll newmax = max(query_max(0, start[v]), query_max(start[v] + sz[v], sz[1]));
		sumtree.erase(make_pair(oldsum, v));
		maxtree.erase(make_pair(oldmax, v));
		sumtree.insert(make_pair(newsum, u));
		maxtree.insert(make_pair(newmax, u));
		solve(v, u);
		sumtree.erase(make_pair(newsum, u));
		maxtree.erase(make_pair(newmax, u));
		sumtree.insert(make_pair(oldsum, v));
		maxtree.insert(make_pair(oldmax, v));
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		cin >> val[i];
	}
	for(int i=1; i<n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(int i=0; i<m; i++) {
		int t, r, k;
		cin >> t >> r >> k;
		queries[r].push_back(make_tuple(t, k, i));
	}

	build(1, 0);
	for(int i=1; i<=n; i++) {
		insert(start[i], val[i]);
	}
	sumtree.insert(make_pair(query_sum(0, sz[1]), 0));
	maxtree.insert(make_pair(query_max(0, sz[1]), 0));
	for(int i=2; i<=n; i++) {
		sumtree.insert(make_pair(query_sum(start[i], start[i] + sz[i]), i));
		maxtree.insert(make_pair(query_max(start[i], start[i] + sz[i]), i));
	}
	solve(1, 0);

	for(int i=0; i<m; i++) {
		cout << ans[i] << nl;
	}

	return 0;
}
