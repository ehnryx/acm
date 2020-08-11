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
const ll MOD = 1e9+7;
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

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	for(int tt=1; tt<=T; tt++) {
		cout << "Case " << tt << ": ";

		int n;
		cin >> n;
		ll all = 1;
		vector<int> p(n), a(n);
		vector<ll> full(n);
		for(int i=0; i<n; i++) {
			cin >> p[i] >> a[i];
			full[i] = power(p[i], a[i], MOD);
			all = all * full[i] % MOD;
		}

		ll ans = all;
		for(int bm=0; bm<1<<n; bm++) {
			ll val = 1;
			ll cnt = 1;
			for(int i=0; i<n; i++) {
				if(bm & 1<<i) {
					cnt = cnt * (a[i] + 1) % MOD;
					val = val * full[i] % MOD;
				} else {
					ll sum = 0;
					for(int j=0, c=1; j<a[i]; j++) {
						sum += c;
						c = (ll)c*p[i] % MOD;
					}
					val = val * (sum % MOD) % MOD;
				}
			}
			ans += val * cnt % MOD;
		}
		cout << ans % MOD << nl;
	}

	return 0;
}
