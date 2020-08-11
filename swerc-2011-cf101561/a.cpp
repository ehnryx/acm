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
const ll MOD = 1e8+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power(ll n, ll e, ll m) {
	ll r = 1;
	for(;e;e/=2) {
		if(e&1) r = r*n % m;
		n = n*n % m;
	}
	return r;
}

ll inverse(ll n, ll m) {
	return power(n, m-2, m);
}

const ll M = 1e9 + 9;
const ll P = 1789;
const ll invP = inverse(P, M);
const ll C = 360000;

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int n, m; cin >> n >> m && n != -1; ) {
		vector<int> a(m);
		for(int i=0; i<m; i++) {
			cin >> a[i];
		}
		sort(a.begin(), a.end());
		for(int i=m-1; i>=0; i--) {
			a[i] -= a[0];
		}

		ll ha = 0;
		ll f = 0;
		ll t = 1;
		for(int i=0; i<m; i++) {
			ha = (ha + a[i] * t) % M;
			if(i+1 < m) {
				f = (f + t) % M;
				t = t*P % M;
			}
		}

		ll init = ha;
		int cnt = 1;
		for(int i=1; i<m; i++) {
			int shift = a[i] - a[i-1];
			ha = (ha * invP - f * shift) % M;
			ha = (ha + t * (C - shift)) % M;
			cnt += (ha == init);
		}

		vector<ll> res(cnt+1);
		for(int d=1; d<=cnt; d++) {
			if(cnt % d != 0) continue;
			res[d] = (res[d] + power(n, m/(cnt/d), MOD)) % MOD;
			for(int j=2*d; j<=cnt; j+=d) {
				res[j] = (res[j] + MOD - res[d]) % MOD;
			}
		}

		ll ans = 0;
		for(int d=1; d<=cnt; d++) {
			if(cnt % d != 0) continue;
			ans += res[d] * inverse(d, MOD) % MOD;
		}
		cout << ans % MOD << nl;
	}

	return 0;
}
