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

const int N = 1000;
ll ans[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		ll x;
		int n;
		cin >> x >> n;

		if (n == 1) {
			ans[0] = x;
		}
		else {
			ll rounds = x / (2*(n-1));
			ans[0] = ans[n-1] = rounds;
			for (int i = 1; i < n-1; i++) {
				ans[i] = 2*rounds;
			}

			int rem = x % (2*(n-1));
			for (int i = 0; i < n-1; i++) {
				if (rem-- > 0) {
					ans[i]++;
				}
			}
			for (int i = n-1; i > 0; i--) {
				if (rem-- > 0) {
					ans[i]++;
				}
			}
		}

		for (int i=0; i<n; i++) {
			cout << ans[i] << " ";
		}
		cout << nl;
	}

	return 0;
}
