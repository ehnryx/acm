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

struct Point {
	int x,o,a;
	bool operator < (const Point& p) const {
		if (x!=p.x) return x<p.x;
		else return o<p.o;
	}
};

const int N = 1<<18;
ll t[2*N], z[2*N];
ll dp[N];

void push(int i) {
	if(z[i]) {
		z[2*i] += z[i];
		z[2*i+1] += z[i];
		t[2*i] += z[i];
		t[2*i+1] += z[i];
		z[i] = 0;
	}
}

void update(int l, int r, ll v, int i=1, int s=0, int e=N-1) {
	if(r<s||e<l) return;
	if(l<=s&&e<=r) {
		t[i] += v;
		z[i] += v;
		return;
	}
	push(i);
	int m = (s+e)/2;
	update(l,r,v,2*i,s,m);
	update(l,r,v,2*i+1,m+1,e);
	t[i] = max(t[2*i],t[2*i+1]);
}

ll query(int l, int r, int i=1, int s=0, int e=N-1) {
	if(r<s||e<l) return -INFLL;
	if(l<=s&&e<=r) {
		return t[i];
	}
	push(i);
	int m = (s+e)/2;
	return max(query(l,r,2*i,s,m),query(l,r,2*i+1,m+1,e));
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	vector<Point> p;
	for(int i=0;i<m;i++) {
		int l,r,a;
		cin >> l >> r >> a;
		p.push_back({l,-2,a});
		p.push_back({r,l,a});
	}
	for (int i=1;i<N;i++) {
		p.push_back({i,-1});
	}
	sort(p.begin(),p.end());

	for(const Point& it:p) {
		if(it.o==-2) {
			update(0, it.x-1, it.a);
		} else if(it.o==-1) {
			dp[it.x] = query(0, it.x-1);
			update(it.x, it.x, dp[it.x]);
		} else {
			update(0, it.o-1, -it.a);
		}
	}

	ll ans = 0;
	for(int i=0;i<N;i++) {
		ans = max(ans, dp[i]);
	}
	cout << ans << nl;

	return 0;
}
