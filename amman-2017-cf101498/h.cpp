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

const int N = 1e6+1;
int ans[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n, s;
		cin >> n >> s;

		if (s == 1) {
			if (n == 1) cout << 1 << nl;
			else cout << -1 << nl;
		}
		else if (s > 9*n) {
			cout << -1 << nl;
		}
		else if (s%2 == 1 && n%2 == 0) {
			cout << -1 << nl;
		}
		else {
			for (int i = 0; i < n/2; i++) {
				ans[n-1-i] = ans[i] = min(s/2,9);
				s -= 2*ans[i];
			}
			if (n%2 == 1) {
				ans[n/2] = s;
			}
			for (int i = 0; i < n; i++) {
				cout << ans[i];
			}
			cout << nl;
		}
	}

	return 0;
}
