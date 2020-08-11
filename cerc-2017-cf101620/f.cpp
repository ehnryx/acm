#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll egcd(ll a, ll b, ll &x, ll &y) {
	if (!b) { x = 1; y = 0; return a; }
	ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	ll n, p, r;
	cin >> n >> p >> r;

	if (r == 0) {
		if (p == 2) {
			if (n < 3) cout << -1 << " " << -1 << nl;
			else cout << 3 << " " << 1 << nl;
		}
		else {
			if (n < p) cout << -1 << " " << -1 << nl;
			else cout << 2 << " " << 1 << nl;
		}
	}
	else {
		if (n >= 2*p) {
			cout << -1 << " " << -1 << nl;
		}
		else if (n >= p) {
			ll fact = 1;
			for (int i = 2; i <= n; i++) {
				if (i != p) fact = fact * i % p;
			}
			ll inv, y;
			egcd(fact, p, inv, y);
			if (inv < 0) inv += p;
			cout << p << " " << inv*r%p << nl;
		}
		else {
			ll fact = 1;
			for (int i = 2; i <= n; i++) {
				fact = fact * i % p;
			}
			ll inv, y;
			egcd(fact, p, inv, y);
			if (inv < 0) inv += p;

			for (int i = n; i > 1; i--) {
				ll x = (r*i%p)*inv%p;
				if (x < i) {
					cout << i << " " << x << nl;
					return 0;
				}
			}
			cout << -1 << " " << -1 << nl;
		}
	}

	return 0;
}
