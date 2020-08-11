#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	ll a, b;
	cin >> a >> b;
	int lim = sqrt(b);
	ll ans = 0;
	for (ll d = 1; d <= lim; d++) {
		ll left = max(d, (a-1)/d) + 1;
		ll right = b/d;
		ans += (right-left+1) * d;
		ans += (right-left+1) * (left + right) / 2;
		if (a <= d*d && d*d <= b) ans += d;
	}
	cout << ans << nl;

	return 0;
}
