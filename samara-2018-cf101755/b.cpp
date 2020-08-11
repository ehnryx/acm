#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll area(const pii& a, const pii& b, const pii& c) {
	return abs((a.first*b.second + b.first*c.second + c.first*a.second)
		- (a.second*b.first + b.second*c.first + c.second*a.first));
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	vector<pii> p;
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		p.push_back(pii(x,y));
	}

	ll ans = INFLL;
	for (int i = 0; i < n; i++) {
		ans = min(ans, area(p[i], p[(i+1)%n], p[(i+2)%n]));
	}
	cout << ans << nl;

	return 0;
}
