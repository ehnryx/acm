#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';
const int N = 1e4+10;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case #" << tt << ": ";
		int m, n, k; cin >> m >> n >> k;
		vector<int> c(n), p(n);
		for (int i = 0; i < n; i++) {
			int t; cin >> t;
			if (t == 0) {
				c[i] = INF;
				cin >> p[i];
			} else {
				cin >> c[i] >> p[i];
			}
		}
		vector<vector<vector<pair<int, int>>>> rules(n);
		for (int i = 0; i < k; i++) {
			int x, y; cin >> x >> y; x--;
			vector<pair<int, int>> cur;
			for (int j = 0; j < y; j++) {
				int u, v; cin >> u >> v; u--;
				cur.emplace_back(u, v);
			}
			rules[x].push_back(cur);
		}
		vector<int> dp = c, ndp(n);
		for (int i = 0; i < k+10; i++) {
			for (int j = 0; j < n; j++) {
				ndp[j] = dp[j];
				for (const auto& v : rules[j]) {
					ll cur = 0;
					for (const auto& pp : v) {
						cur += (ll) pp.second * dp[pp.first];
					}
					if (cur < ndp[j]) {
						ndp[j] = cur;
					}
				}
			}
			dp.swap(ndp);
		}
		//for (int i : dp) cerr << i << " "; cerr << nl;
		vector<ll> kdp(N);
		for (int i = 0; i < n; i++) {
			for (int j = dp[i]; j <= m; j++) {
				kdp[j] = max(kdp[j], kdp[j-dp[i]] + p[i]);
			}
		}
		cout << kdp[m] << nl;
	}

	return 0;
}
