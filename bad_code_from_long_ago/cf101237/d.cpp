#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

ld power(ld b, int e) {
	ld res = 1;
	while (e > 0) {
		if (e & 1)
			res *= b;
		b *= b;
		e >>= 1;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	ll n, k;
	cin >> n >> k;

	ld ans = 0;
	ld reci = ((ld)1)/k;
	int half = n/2;

	if (k == 1) {
		ans = n*(n+1)/2;
	}
	else if (n == 1) {
		ans = 1;
	}
	else if (n == 2) {
		ans = 2 + reci;
	}
	else if (n % 2 == 1) {
		ld diff = (2*n-3)*reci - 3*power(reci, half+1);
		diff -= 4*(reci*reci*(1-power(reci, half-1)) / (1-reci));
		diff /= (1-reci);
		ans = n + diff;
	}
	else {
		ld diff = (2*n-3)*reci - 5*power(reci, half);
		diff -= 4*(reci*reci*(1-power(reci, half-2)) / (1-reci));
		diff /= (1-reci);
		ans = n + diff + power(reci, half);
	}

	cout << ans << nl;

	return 0;
}
