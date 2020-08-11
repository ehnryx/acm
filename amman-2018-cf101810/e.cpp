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
// Extended Euclidean Algorithm (UBC)
// egcd(a,b,x,y) calculates x,y such that ax+by=gcd(a,b)
// To find a^{-1} mod m, use egcd(a,m,x,y) and x = a^{-1}
// Returns gcd(a,b)
ll egcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	} else {
		ll d = egcd(b, a%b, y, x);
		y -= x * (a/b);
		return d;
	}
}
//*/

////////////////////////////////////////////////////////////////////////
// Int struct for operations on a prime field (TESTED)
// WARNING: slow
struct Int {
	ll x;
	Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
	operator ll() { return x; }
	Int operator + (const Int& n) const { return Int(x + n.x); }
	Int operator - (const Int& n) const { return Int(x - n.x); }
	Int operator * (const Int& n) const { return Int(x * n.x); }
	Int operator / (const Int& n) const { return Int(x * n.inv()); }
	void operator += (const Int& n) { x = (x + n.x) % MOD; }
	void operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; }
	void operator *= (const Int& n) { x = (x * n.x) % MOD; }
	void operator /= (const Int& n) { x = (x * n.inv()) % MOD; }
	ll inv() const {
		if (x == 0) throw runtime_error("divide by zero");
		ll c, d;
		egcd(x, MOD, c, d);
		return (c < 0) ? c+MOD : c;
	}
};
//*/

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;

		Int ans = 0;
		Int v = 1;
		int a;
		for (int i=0; i<n; i++) {
			cin >> a;
			ans *= a;
			ans += v * Int(a-1);
			v *= a;
		}

		cout << ans << nl;
	}

	return 0;
}
