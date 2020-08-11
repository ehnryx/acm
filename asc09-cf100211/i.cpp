//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "traces"

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

const int M = 10 + 1;
bool adj[M][M];
vector<int> idx[M];

const int N = 1<<17;
struct BIT {
	int bit[N];
	BIT() { memset(bit, 0, sizeof bit); }
	void insert(int i, int v) {
		for(i++; i<N; i+=i&-i) {
			bit[i] += v;
		}
	}
	int query(int i) {
		int res = 0;
		for(i++; i>0; i-=i&-i) {
			res += bit[i];
		}
		return res;
	}
	int query_range(int l, int r) {
		return query(r) - query(l-1);
	}
};

BIT bit[M];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
//*/

	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		char a, b;
		cin >> a >> b;
		adj[a-'a'][b-'a'] = adj[b-'a'][a-'a'] = true;
	}
	for(int i=0; i<n; i++) {
		adj[i][i] = true;
	}

	string s;
	cin >> s;

	string t;
	cin >> t;

	int len = s.size();
	if(len != t.size()) {
		cout << "NO" << nl;
		return 0;
	}

	for(int i=0; i<len; i++) {
		int c = s[i] - 'a';
		idx[c].push_back(i);
		bit[c].insert(i, 1);
	}
	for(int i=0; i<M; i++) {
		reverse(idx[i].begin(), idx[i].end());
	}

	for(int i=0, j=0; i<len; i++) {
		int c = t[i] - 'a';
		if(idx[c].empty()) {
			cout << "NO" << nl;
			return 0;
		}
		int take = idx[c].back();
		idx[c].pop_back();
		bit[c].insert(take, -1);
		for(int k=0; k<M; k++) {
			if(bit[k].query_range(j, take) && !adj[c][k]) {
				cout << "NO" << nl;
				return 0;
			}
		}
	}

	cout << "YES" << nl;

	return 0;
}
