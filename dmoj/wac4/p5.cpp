//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int find(int i, vector<int>& dsu) {
	if(dsu[i] == -1) return i;
	return dsu[i] = find(dsu[i], dsu);
}
void link(int i, int j, vector<int>& dsu, vector<multiset<ll>>& sz, vector<ll>& offset) {
	i = find(i, dsu);
	j = find(j, dsu);
	if(i == j) return;
	if(sz[i].size() > sz[j].size()) swap(i, j);
	dsu[i] = j;
	for(ll v : sz[i]) {
		sz[j].insert(v + offset[i] - offset[j]);
	}
	sz[i].clear();
}

void solve_small(int n, int q) {
	vector<vector<int>> dsu(q+1);
	vector<vector<multiset<ll>>> sz(q+1);
	vector<vector<ll>> offset(q+1);
	dsu[0].resize(n+1, -1);
	sz[0].resize(n+1, multiset<ll>());
	offset[0].resize(n+1, 0);

	for(int i=1; i<=n; i++) {
		ll v;
		cin >> v;
		sz[0][i].insert(v);
	}

	ll last = 0;
	for(int i=1; i<=q; i++) {
		int t;
		cin >> t;
		if(t == 1) {
			ll j, a, b;
			cin >> j >> a >> b;
			j ^= last;
			a ^= last;
			b ^= last;
			if(j<0 || j>=i) exit(0);
			dsu[i] = dsu[j];
			sz[i] = sz[j];
			offset[i] = offset[j];
			link(a, b, dsu[i], sz[i], offset[i]);
		} else if(t == 2) {
			ll j, a;
			cin >> j >> a;
			j ^= last;
			a ^= last;
			if(j<0 || j>=i) exit(0);
			dsu[i] = dsu[j];
			sz[i] = sz[j];
			offset[i] = offset[j];
			a = find(a, dsu[i]);
			last = *sz[i][a].rbegin() + offset[i][a];
			sz[i][a].erase(prev(sz[i][a].end()));
			sz[i][a].insert(-offset[i][a]);
			cout << last << nl;
		} else if(t == 3) {
			ll j, a, c;
			cin >> j >> a >> c;
			j ^= last;
			a ^= last;
			c ^= last;
			if(j<0 || j>=i) exit(0);
			dsu[i] = dsu[j];
			sz[i] = sz[j];
			offset[i] = offset[j];
			a = find(a, dsu[i]);
			offset[i][a] += c;
		}
	}
}

void solve_large_and_cry(int n, int q) {
	vector<int> dsu(n+1, -1);
	vector<multiset<ll>> sz(n+1);
	vector<ll> offset(n+1, 0);

	for(int i=1; i<=n; i++) {
		int v;
		cin >> v;
		sz[i].insert(v);
	}

	ll last = 0;
	for(int i=1; i<=q; i++) {
		int t;
		cin >> t;
		if(t == 1) {
			ll j, a, b;
			cin >> j >> a >> b;
			a ^= last;
			b ^= last;
			link(a, b, dsu, sz, offset);
		} else if(t == 2) {
			ll j, a;
			cin >> j >> a;
			a ^= last;
			a = find(a, dsu);
			last = *sz[a].rbegin() + offset[a];
			sz[a].erase(prev(sz[a].end()));
			sz[a].insert(-offset[a]);
			cout << last << nl;
		} else if(t == 3) {
			ll j, a, c;
			cin >> j >> a >> c;
			a ^= last;
			c ^= last;
			a = find(a, dsu);
			offset[a] += c;
		}
	}
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, q;
	cin >> n >> q;

	if(n <= 2000 && q <= 2000) {
		solve_small(n, q);
	} else {
		solve_large_and_cry(n, q);
	}

	return 0;
}
