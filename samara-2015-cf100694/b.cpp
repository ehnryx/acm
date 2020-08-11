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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int p, n, x;
	cin >> p >> n >> x;

	int ans = x/p + x%p;
	if (p*(x/p+1) > n) ans = min(ans, x/p+1 + n-x);
	else ans = min(ans, x/p+1 + p-(x%p));

	int other = n/p+1 + min((n-x)/p + (n-x)%p, (n-x)/p+1 + p-(n-x)%p);

	cerr << "ans: " << ans << nl;
	cerr << "other: " << other << nl;

	cout << min(ans, other) << nl;

	return 0;
}
