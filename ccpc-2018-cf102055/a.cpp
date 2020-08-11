#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case " << tt << ": ";
		int n, m; cin >> n >> m;
		vector<int> d(n);
		for (int& i : d) cin >> i;
		vector<pair<int, int>> t(n);
		for (int i = 0; i < n; i++) {
			cin >> t[i].first; t[i].second = i;
		}
		sort(t.begin(), t.end(), [&](const auto& a, const auto& b) {
			return d[a.second] < d[b.second];
		});
		int curt = 0;
		for (int i = 0; i < n; i++) {
			if (curt + t[i].first > m) {
				cout << i << nl;
				goto end;
			}
			curt += t[i].first;
		}
		cout << n << nl;
		end:;
	}

	return 0;
}
