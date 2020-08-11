#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "journey"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<16;
const int M = 5e6 + 1;

ll rmq[M];
int ls[M], rs[M];
int root[N];

int p[N], d[N];
ll dp[N];

struct PSegTree {
	int sid;
	PSegTree() { clear(); }
	void clear() {
		sid = 0;
		rmq[0] = INFLL;
	}

	void insert(int& ver, int old, int x, ll v, int s=0, int e=N-1) {
		ver = ++sid;
		if(s == e) {
			rmq[ver] = min(rmq[old], v);
			return;
		}
		ls[ver] = ls[old];
		rs[ver] = rs[old];

		int m = (s+e)/2;
		if(x <= m) insert(ls[ver], ls[old], x, v, s, m);
		else insert(rs[ver], rs[old], x, v, m+1, e);
		rmq[ver] = min(rmq[ls[ver]], rmq[rs[ver]]);
		assert(ver != ls[ver] && ver != rs[ver]);
	}

	ll query(int ver, int l, int r, int s=0, int e=N-1) {
		if(r<s || e<l) return INFLL;
		if(l<=s && e<=r) {
			return rmq[ver];
		}

		int m = (s+e)/2;
		return min(query(ls[ver], l, r, s, m), query(rs[ver], l, r, m+1, e));
	}
};

PSegTree segt;

ll value(int r, int n) {
	segt.clear();
	dp[1] = 0;
	segt.insert(root[1], root[0], 1, 0);
	for(int i=2; i<=n; i++) {
		dp[i] = segt.query(root[i-1], i-r, i-1);
		segt.insert(root[i], root[i-1], i, dp[i] + d[i]);
	}
	return dp[n] + n-1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	if(fopen(FILENAME ".in", "r")) {
		freopen(FILENAME ".in", "r", stdin);
		freopen(FILENAME ".out", "w", stdout);
	}

	int n, t;
	cin >> n >> t;
	for(int i=1; i<n; i++) {
		cin >> p[i];
	}
	for(int i=2; i<n; i++) {
		cin >> d[i];
	}

	int l = 1;
	int r = n-1;
	while(l<r) {
		int m = (l+r)/2;
		if(value(m, n) <= t) {
			r = m;
		} else {
			l = m+1;
		}
	}

	int ans = INF;
	for(int i=r; i<n; i++) {
		ans = min(ans, p[i]);
	}
	cout << ans << nl;

	return 0;
}
