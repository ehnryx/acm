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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;

		string s;
		cin >> s;

		int unmatched = 0;
		for (int i = 0; i < n/2; i++) {
			if (s[i] != s[n-1-i]) unmatched++;
		}

		int ans = 0;
		int p;
		char c;
		for (int i = 0; i < m; i++) {
			cin >> p >> c;
			--p;

			int before = (s[p] != s[n-1-p]);
			s[p] = c;
			int after = (s[p] != s[n-1-p]);

			unmatched += after-before;
			if (unmatched == 0) {
				ans++;
			}
		}

		cout << ans << nl;
	}

	return 0;
}
