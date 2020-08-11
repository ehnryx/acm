#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 4e5+7;
ll fact[N], invf[N];
ll mid[N];

ll inverse(ll n) {
	ll ans = 1;
	for (int m = MOD-2; m > 0; m /= 2) {
		if (m&1) ans = ans*n % MOD;
		n = n*n % MOD;
	}
	return ans;
}

void init() {
	fact[0] = invf[0] = 1;
	for (int i=1; i<N; i++) {
		fact[i] = fact[i-1] * i % MOD;
		invf[i] = inverse(fact[i]);
	}
}

ll ncr(int n, int r) {
	if (r<0 || r>n) return 0;
	return (fact[n]*invf[r] % MOD) * invf[n-r] % MOD;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	init();

	int a, b, c;
	cin >> a >> b >> c;

	for (int i=0; i<=a+b; i++) {
		int cnt = a+b-i;
		int na, nb;
		// a first
		na = (cnt+1)/2 - 1;
		nb = (cnt)/2 - 1;
		mid[i] = ncr(a-1, na) * ncr(b-1, nb) % MOD;
		// b first
		na = (cnt)/2 - 1;
		nb = (cnt+1)/2 - 1;
		mid[i] += ncr(a-1, na) * ncr(b-1, nb) % MOD;
		mid[i] %= MOD;
	}

	ll ans = 0;
	for (int i=0; i<=a+b; i++) {
		ans += mid[i] * ncr(a+b+1-i, c-i) % MOD;
	}
	cout << ans % MOD << nl;

	return 0;
}
