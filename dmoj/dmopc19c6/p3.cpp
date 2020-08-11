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

const int N = 1 << 19;
ll z[2*N], tot[2*N], p2[N];

void push(int i) {
	if(z[i]) {
		tot[2*i] += z[i]/2;
		tot[2*i+1] += z[i]/2;
		z[2*i] += z[i]/2;
		z[2*i+1] += z[i]/2;
		z[i] = 0;
	}
}

void pull(int i) {
	tot[i] = tot[2*i] + tot[2*i+1];
}

ll insert(int l, int r, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l || tot[i] == e-s+1) return 0;
	if(l<=s && e<=r && tot[i] == 0) {
		z[i] = tot[i] = e-s+1;
		return (p2[e+1] + MOD - p2[s]) % MOD;
	}
	push(i);
	int m = (s+e) / 2;
	ll left = insert(l, r, 2*i, s, m);
	ll right = insert(l, r, 2*i+1, m+1, e);
	pull(i);
	return (left + right) % MOD;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	p2[0] = 1;
	for(int i=1; i<=n; i++) {
		p2[i] = p2[i-1] * 2 % MOD;
	}

	ll ans = 0;
	for(int i=n-1; i>=0; i--) {
		char c;
		cin >> c;
		if(c == '1') {
			ans = (ans + insert(i, i)) % MOD;
		}
	}

	for(int i=0; i<m; i++) {
		int l, r;
		cin >> l >> r;
		ans = (ans + insert(n-r, n-l)) % MOD;
		cout << ans << nl;
	}

	return 0;
}
