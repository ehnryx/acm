#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int n, k;
int val[12];
ll dp[1<<12][12][701];
ll solve(int left, int bm, int cur, int points) {
	if (points < 0) return 0;
	if (left == 0) return 1;
	if (dp[bm][cur][points] != -1) {
		return dp[bm][cur][points];
	}
	
	ll res = 0;
	for (int i = 0; i < n; i++) {
		if ((bm & 1<<i) == 0 && i != cur) {
			int add = max(0, 1 + val[cur] - val[i]);
			res += solve(left-1, bm | 1<<i, i, points - add*left);
		}
	}
	return dp[bm][cur][points] = res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	memset(dp, -1, sizeof(dp));

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	sort(val, val+n);

	cout << solve(n, 0, n-1, k) << nl;

	return 0;
}
