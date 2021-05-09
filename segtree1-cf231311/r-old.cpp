#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<18;
//template<int N> struct SegTree {
	ll segt[2*N], lazy[2*N];

	//SegTree() {
		//memset(segt, 0, sizeof segt);
		//memset(lazy, 0, sizeof lazy);
	//}

	void push(int i) {
		if (lazy[i]) {
			segt[2*i] += lazy[i];
			segt[2*i+1] += lazy[i];
			lazy[2*i] += lazy[i];
			lazy[2*i+1] += lazy[i];
			lazy[i] = 0;
		}
	}

	void pull(int i) {
		segt[i] = min(segt[2*i], segt[2*i+1]);
	}

	void setv(int x, ll v, int i=1, int s=0, int e=N-1) {
		if (s==e) {
			segt[i] = v;
			return;
		}
		push(i);
		int m = (s+e)/2;
		if (x<=m) setv(x, v, 2*i, s, m);
		else setv(x, v, 2*i+1, m+1, e);
		pull(i);
	}

	void update(int l, int r, ll v, int i=1, int s=0, int e=N-1) {
		if (r<s || e<l) return;
		if (l<=s && e<=r) {
			segt[i] += v;
			lazy[i] += v;
			return;
		}
		push(i);
		int m = (s+e)/2;
		update(l, r, v, 2*i, s, m);
		update(l, r, v, 2*i+1, m+1, e);
		pull(i);
	}

	ll query(int l, int r, int i=1, int s=0, int e=N-1) {
		if (r<s || e<l) return INFLL;
		if (l<=s && e<=r) {
			return segt[i];
		}
		push(i);
		int m = (s+e)/2;
		return min(query(l,r,2*i,s,m), query(l,r,2*i+1,m+1,e));
	}

	void update_range(int l, int r, ll v) {
		if (l > r) {
			update(l, N-1, v);
			update(0, r, v);
		} else {
			update(l, r, v);
		}
	}

	ll query_range(int l, int r) {
		if (l > r) {
			return min(query(l, N-1), query(0, r));
		} else {
			return query(l, r);
		}
	}
//};

//SegTree<(1<<18)> segt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	//segt.
	update_range(0, (1<<18)-1, INFLL);

	int n;
	cin >> n;
	For(i,n) {
		int v;
		cin >> v;
		//segt.
		setv(i, v);
	}

	int m;
	cin >> m;
	string line;
	getline(cin, line);
	For(i,m) {
		getline(cin, line);
		istringstream in(line);
		vector<int> q;
		for (int v; in >> v; ) {
			q.push_back(v);
		}
		if (q.size() == 2) {
			//cout << segt.query_range(q[0],q[1]) << nl;
			cout << query_range(q[0],q[1]) << nl;
		} else {
			//segt.
			update_range(q[0],q[1],q[2]);
		}
	}

	return 0;
}
