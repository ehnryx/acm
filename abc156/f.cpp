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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 5000 + 1;
ll d[N], dk[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	ll k, q;
	cin >> k >> q;

	for(int i=0; i<k; i++) {
		cin >> d[i];
	}

	while(q--) {
		ll n, x, m;
		cin >> n >> x >> m;
		n -= 1;
		x %= m;

		ll len = 0;
		for(int i=0; i<k; i++) {
			dk[i] = d[i] % m;
			if(dk[i] == 0) dk[i] = m;
			len += dk[i];
		}

		ll step = len % m;
		int bad = 0;

		if(step != 0) {
			ll slen = step * (n/k);
			bad += (x + slen) / m;
		}

		bad += (len / m) * (n / k);
		x = (x + step * (n/k)) % m;
		for(int i=(n/k)*k; i<n; i++) {
			ll nx = (x + dk[i%k]) % m;
			if(nx <= x) bad++;
			x = nx;
		}

		cout << n-bad << nl;
	}

	return 0;
}
