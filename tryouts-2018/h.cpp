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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int r, s;
	cin >> r >> s;

	int n;
	cin >> n;

	int c; ld t;
	int dp[n+1][n+1];
	memset(dp, INF, sizeof dp);

	dp[0][0] = 0;
	for (int i=1; i<=n; i++) {
		cin >> c >> t;
		for (int j=0; j<i; j++) {
			dp[i][j] = min(dp[i][j], dp[i-1][j]);
			if ((s+5*j+i-1-j) > t*(r+i-1)) {
				dp[i][j+1] = min(dp[i][j+1], dp[i-1][j]);
			} else {
				dp[i][j+1] = min(dp[i][j+1], dp[i-1][j] + c);
			}
		}
	}

	int ans = INF;
	for (int j=0; j<=n; j++) {
		if ((s+5*j+n-j) >= 4*(r+n)) {
			ans = min(ans, dp[n][j]);
		}
	}
	if (ans == INF) {
		cout << -1 << nl;
	} else {
		cout << ans << nl;
	}

	return 0;
}
