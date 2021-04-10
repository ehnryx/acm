#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case #" << tt << ": ";
		int n; cin >> n;
		vector<int> p(n);
		for (int i = 0; i < n; i++) {
			cin >> p[i];
		}
		sort(p.rbegin(), p.rend());
		int ans = 0;
		for (int i = 0; i < n; i += 3) {
			ans += p[i];
			if (i+1 < n) ans += p[i+1];
		}
		cout << ans << nl;
	}

	return 0;
}
