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

	string s;
	cin >> s;
	int n = s.size();

	vector<int> cnt[10];
	for (int i=n-1; i>=0; i--) {
		cnt[s[i]-'0'].push_back(i);
	}

	int ans = INF;

	if (cnt[0].size() >= 2) {
		ans = min(ans, abs(n-1-cnt[0][0]) + abs(n-2-cnt[0][1]));
		ans = min(ans, abs(n-2-cnt[0][0]) + abs(n-1-cnt[0][1]));
	}

	if (cnt[2].size() >= 1 && cnt[5].size() >= 1 && cnt[0].size() < n-2) {
		int cur = 0;
		if (cnt[2][0] == 0 || cnt[5][0] == 0) {
			int other = false;
			int nxt = 1;
			while (s[nxt] == '0' || nxt == cnt[5][0] || nxt == cnt[2][0]) { 
				other |= (nxt == cnt[5][0] || nxt == cnt[2][0]);
				nxt++;
			}
			cur = abs(nxt-1-other);
		}
		if (cnt[2][0] == n-1 && cnt[5][0] == n-2) {
			ans = min(ans, 1);
		} else {
			ans = min(ans, cur + abs(n-2-cnt[2][0]) + abs(n-1-cnt[5][0]));
		}
	}

	if (cnt[5].size() >= 1 && cnt[0].size() >= 1 && cnt[0].size() < n-1) {
		int cur = 0;
		if (cnt[5][0] == 0) {
			int nxt = 1;
			while (s[nxt] == '0') { nxt++; }
			cur = abs(nxt-1);
		}
		if (cnt[5][0] == n-1 && cnt[0][0] == n-2) {
			ans = min(ans, 1);
		} else {
			ans = min(ans, cur + abs(n-2-cnt[5][0]) + abs(n-1-cnt[0][0]));
		}
	}

	if (cnt[7].size() >= 1 && cnt[5].size() >= 1 && cnt[0].size() < n-2) {
		int cur = 0;
		if (cnt[7][0] == 0 || cnt[5][0] == 0) {
			int other = false;
			int nxt = 1;
			while (s[nxt] == '0' || nxt == cnt[7][0] || nxt == cnt[5][0]) { 
				other |= (nxt == cnt[7][0] || nxt == cnt[5][0]);
				nxt++;
			}
			cur = abs(nxt-1-other);
		}
		if (cnt[7][0] == n-1 && cnt[5][0] == n-2) {
			ans = min(ans, 1);
		} else {
			ans = min(ans, cur + abs(n-2-cnt[7][0]) + abs(n-1-cnt[5][0]));
		}
	}

	if (ans == INF) cout << -1 << nl;
	else cout << ans << nl;

	return 0;
}
