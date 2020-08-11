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

////////////////////////////////////////////////////////////////////////
// Int struct for operations on a prime field (TESTED)
// WARNING: slow
struct Int {
	ll x;
	Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
	operator ll&() { return x; }
	Int operator + (const Int& n) const { return Int(x + n.x); }
	Int operator - (const Int& n) const { return Int(x - n.x); }
	Int operator * (const Int& n) const { return Int(x * n.x); }
	void operator += (const Int& n) { x = (x + n.x) % MOD; }
	void operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; }
	void operator *= (const Int& n) { x = (x * n.x) % MOD; }
};

Int power(Int b, int e) {
	Int p = b;
	Int res = 1;
	while (e) {
		if (e&1) res *= p;
		p *= p;
		e /= 2;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, k;
	cin >> n >> k;
	if (n == 1) {
		cout << 1 << nl;
		return 0;
	}

	Int ans = 1;
	int e = (n-1)/(k+1);
	ans += Int(2) * Int(k+1) * (power(2, e) - Int(1));
	Int extra = (n-1)%(k+1);
	ans += Int(2) * extra * power(2, e);

	cout << ans << nl;

	return 0;
}
