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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int D = 10000;

ll lower(ll g, ll t) {
	ll l = 0;
	ll r = INFLL;
	while(l<r) {
		ll v = (l+r)/2;
		__int128 nv = (__int128)v * (D+t);
		__int128 fv = nv / D;
		__int128 cv = (nv+D-1) / D;
		ll res = (nv - fv*D < cv*D - nv ? fv : cv);
		if(res < g) {
			l = v+1;
		} else {
			r = v;
		}
	}
	return r;
}

ll upper(ll g, ll t) {
	ll l = 0;
	ll r = INFLL;
	while(l<r) {
		ll v = (l+r)/2;
		__int128 nv = (__int128)v * (D+t);
		__int128 fv = nv / D;
		__int128 cv = (nv+D-1) / D;
		ll res = (nv - fv*D < cv*D - nv ? fv : cv);
		if(res <= g) {
			l = v+1;
		} else {
			r = v;
		}
	}
	return r;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while(T--) {
		ld aa, bb, tt;
		cin >> aa >> bb >> tt;
		ll a = llround(aa*100);
		ll b = llround(bb*100);
		ll t = llround(tt*100);
		ll l = lower(a, t);
		ll r = upper(b, t);
		cout << (b-a+1) - (r-l) << nl;
	}

	return 0;
}
