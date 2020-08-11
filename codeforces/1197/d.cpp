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

const int N = 1<<19;
int a[N];
ll p[N];

struct SegTree {
	ll segt[2*N], lazy[2*N];
	SegTree() {
		memset(lazy, 0, sizeof lazy);
		fill(segt, segt+2*N, -INFLL);
	}

	void build() {
		DOWN(i,1,N-1) segt[i] = max(segt[2*i], segt[2*i+1]);
	}
	void set(int i, ll v) {
		segt[i+N] = v;
	}

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
		segt[i] = max(segt[2*i], segt[2*i+1]);
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
		update(l,r,v,2*i,s,m);
		update(l,r,v,2*i+1,m+1,e);
		pull(i);
	}

	ll query(int l, int r, int i=1, int s=0, int e=N-1) {
		if (r<s || e<l) return -INFLL;
		if (l<=s && e<=r) {
			return segt[i];
		}
		push(i);
		int m = (s+e)/2;
		return max(query(l,r,2*i,s,m), query(l,r,2*i+1,m+1,e));
	}
};

SegTree segt[10];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m; ll k;
	cin >> n >> m >> k;

	FOR(i,1,n) {
		cin >> a[i];
		p[i] = p[i-1] + a[i];
		segt[i%m].set(i, p[i] - k*((i+m-1)/m));
	}
	For(i,m) {
		segt[i].build();
	}

	ll ans = 0;
	FOR(i,1,n) {
		For(j,m) {
			ans = max(ans, segt[j].query(i, n) - p[i-1]);
		}
		segt[i%m].update(i, n, k);
	}
	cout << ans << nl;

	return 0;
}
