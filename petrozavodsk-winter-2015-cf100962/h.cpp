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

ld sqr(const ld& x) { return x*x; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);

	int w, h, n;
	cin >> w >> h >> n;

	ld ans = 0;

	if (n%2 == 0) {
		ld fact = 1;
		for (int i=1; i<=n/2; i++) {
			fact *= (ld)(2*i-1) / (2*i);
		}
		ans = fact / (sqr(n/2+1)*sqr(n/2+1));

		for (int i=1; i<=n/2; i++) {
			fact *= (ld)(n/2-i+1)/(n/2+i);
			ans += 2 * fact / (sqr(n/2-i+1)*sqr(n/2+i+1));
		}
	}

	else {
		ld fact = 1;
		for (int i=1; i<=n/2; i++) {
			fact *= (ld)(2*i-1) / (2*i);
		}
		fact *= (ld)(n)/(n/2+1) / 2;

		for (int i=0; i<=n/2; i++) {
			ans += 2 * fact / (sqr(n/2-i+1)*sqr(n/2+i+2));
			fact *= (ld)(n/2-i)/(n/2+i+2);
		}
	}

	ans *= w*h;
	cout << ans << nl;

	return 0;
}
