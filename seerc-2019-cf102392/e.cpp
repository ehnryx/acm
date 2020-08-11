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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, k;
	cin >> n >> k;

	ll lc, pc, lm, pm;
	cin >> lc >> pc >> lm >> pm;

	ll t, d;
	cin >> t >> d;

	vector<ll> a(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());

	int bad = 0;
	int cars = 0;
	ll need = 0;
	ll have = 0;
	for(int i=0; i<n; i++) {
		if(a[i] + d < lm) {
			bad++;
		} else if(a[i] < lm) {
			need += lm - a[i];
		} else {
			have += min(d, a[i] - lm);
		}
		cars += (a[i] + d >= lc);
	}

	ll ans = (!bad && need <= have) ? need*t + pm*n : INFLL;

	for(int j=1; j<=cars && j*k<n+k; j++) {
		// make n-j a driver
		if(a[n-j] < lm) {
			need -= lm - a[n-j];
		} else {
			have -= min(d, a[n-j] - lm);
		}
		if(a[n-j] < lc) {
			need += lc - a[n-j];
		} else {
			have += min(d, a[n-j] - lc);
		}

		// make the next k-1 passengers
		for(int i=(j-1)*(k-1); i<min(n-j,j*(k-1)); i++) {
			if(a[i] + d < lm) {
				bad--;
			} else if(a[i] < lm) {
				need -= lm - a[i];
			} else {
				have -= min(d, a[i] - lm);
			}
			have += min(d, a[i] - 1);
		}

		if(!bad && need <= have) {
			ans = min(ans, need*t + pc*j + pm*max(0,n-j*k));
		}
	}

	if(ans < INFLL) {
		cout << ans << nl;
	} else {
		cout << -1 << nl;
	}

	return 0;
}
