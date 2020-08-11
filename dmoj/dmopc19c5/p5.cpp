#pragma GCC optimize("O3")
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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int L = 20;
const int N = 1<<L;

int dsu[N];
int find(int i) {
	if(dsu[i] == -1) return i;
	return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
	if(find(i) != find(j)) {
		dsu[find(i)] = find(j);
	}
}

vector<pair<int,int>> adj[N];
int xval[N];

void build(int u, int p) {
	for(auto [v, c] : adj[u]) {
		if(v == p) continue;
		xval[v] = xval[u] ^ c;
		build(v, u);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	memset(dsu, -1, sizeof dsu);

	int n, m, g;
	cin >> n >> m >> g;
	if(g == 0) {
		cout << "yes" << nl;
		return 0;
	}

	vector<tuple<int,int,int>> edges;
	for(int i=0; i<m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if(find(a) != find(b)) {
			link(a, b);
			adj[a].push_back(make_pair(b, c));
			adj[b].push_back(make_pair(a, c));
		} else {
			edges.push_back(make_tuple(a, b, c));
		}
	}
	build(1, 0);

	vector<int> v;
	for(auto [a, b, c] : edges) {
		int cyc = xval[a] ^ xval[b] ^ c;
		v.push_back(cyc);
	}
	sort(v.begin(), v.end(), greater<int>());

	n = v.size();
	int pre = 0;
	vector<int> base;
	for(int i=0; i<n; i++) {
		if(v[i] == 0) break;
		int cur = __builtin_clz(v[i]);
		if(cur != pre) {
			base.push_back(v[i]);
			for(int j=i+1; j<n; j++) {
				if(__builtin_clz(v[j]) == cur) {
					v[j] ^= v[i];
				}
			}
			sort(v.begin()+i+1, v.end(), greater<int>());
			pre = cur;
		}
	}

	base.push_back(g);
	n = base.size();
	sort(base.begin(), base.end(), greater<int>());
	pre = 0;
	int cnt = 0;
	for(int i=0; i<n; i++) {
		if(base[i] == 0) break;
		int cur = __builtin_clz(base[i]);
		if(cur != pre) {
			cnt++;
			for(int j=i+1; j<n; j++) {
				if(__builtin_clz(base[j]) == cur) {
					base[j] ^= base[i];
				}
			}
			sort(base.begin()+i+1, base.end(), greater<int>());
			pre = cur;
		}
	}

	if(cnt == n) {
		cout << "no" << nl;
	} else {
		cout << "yes" << nl;
	}

	return 0;
}
