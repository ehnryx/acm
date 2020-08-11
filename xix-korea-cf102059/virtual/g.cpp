#include <bits/stdc++.h>
using namespace std;

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
const int N = 25e4+10, K = 10;

int n, k;
int w[N];
/*
ll dp[N][2*K][3][K];

ll solve(int pos, int swap, int skip, int remk) {
	if (remk < 0) return INFLL;
	if (swap < -k || swap > k) return INFLL;
	if (pos >= n && swap == 0 && skip > 0) return 0;
	if (pos >= n) return INFLL;
	if (dp[pos][swap+K][skip][remk] != -1) return dp[pos][swap+K][skip][remk];
	ll ans = INFLL;
	if (skip > 0) {
		ans = min(ans, solve(pos+1, swap, skip-1, remk));
		ans = min(ans, solve(pos+1, swap+1, skip-1, remk) + w[pos]);
	}
	ans = min(ans, solve(pos+1, swap-1, 2, remk-1));
	ans = min(ans, solve(pos+1, swap, 2, remk) + w[pos]);
	return dp[pos][swap+K][skip][remk] = ans;
}
*/

inline ll get(int swap, int skip, int remk, const vector<vector<vector<ll>>>& v) {
	if (remk < 0) return INFLL;
	if (swap < -k || swap > k) return INFLL;
	return v[swap+K][skip][remk];
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> w[i];
	}
	vector<vector<vector<ll>>> cur(2*K, vector<vector<ll>>(3, vector<ll>(K)));
	auto prev = cur;
	for (int swap = -K; swap < K; swap++) {
		for (int skip = 0; skip <= 2; skip++) {
			for (int remk = 0; remk < K; remk++) {
				if (swap == 0 && skip > 0) prev[swap+K][skip][remk] = 0;
				else prev[swap+K][skip][remk] = INFLL;
			}
		}
	}
	for (int pos = n-1; pos >= 0; pos--) {
		for (int swap = -K; swap < K; swap++) {
			for (int skip = 0; skip <= 2; skip++) {
				for (int remk = 0; remk <= k; remk++) {
					if (swap < -k || swap > k) {
						cur[swap+K][skip][remk] = INFLL;
						continue;
					}
					ll ans = INFLL;
					if (skip > 0) {
						ans = min(ans, get(swap, skip-1, remk, prev));
						ans = min(ans, get(swap+1, skip-1, remk, prev) + w[pos]);
					}
					ans = min(ans, get(swap-1, 2, remk-1, prev));
					ans = min(ans, get(swap, 2, remk, prev) + w[pos]);
					//if (ans != 0 && ans != INFLL) cerr << "! " << ans << nl;
					cur[swap+K][skip][remk] = ans;
				}
			}
		}
		prev.swap(cur);
	}
	cout << prev[K][1][k] << nl;

	return 0;
}
