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

// assume 0 <= x < 1
pair<ll, ll> approximate(ld x, ll N) {
	assert(0 <= x && x < 1);
	ll op = 1, oq = 0, p = 0, q = 1, a = 0;
	for(ld y = x; ; ) {
		if(isinf(y = 1/(y-a))) return make_pair(p, q);
		a = floor(y);
		ll np = p*a + op, nq = q*a + oq;
		if(nq > N) {
			ll t = (N - oq) / q;
			ll tp = t*p + op, tq = t*q + oq;
			ld A = (ld)p/q, B = (ld)tp/tq;
			return abs(A-x) < abs(B-x) ? make_pair(p, q) : make_pair(tp, tq);
		}
		op = p; p = np;
		oq = q; q = nq;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while(T--) {
		int n, m; ld x;
		cin >> n >> m >> x;
		auto [a, b] = approximate(x, m);
		assert(__gcd(a, b) == 1);
		cout << n << " " << a << "/" << b << nl;
	}

	return 0;
}
