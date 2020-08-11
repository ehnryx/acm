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

	int n;
	cin >> n;

	int a[n+1], b[n+1];
	for (int i=1; i<=n; i++) {
		cin >> a[i];
	}
	for (int i=1; i<=n; i++) {
		cin >> b[i];
	}

	int dp[n+1][3];
	dp[0][0] = 0;
	dp[0][1] = -INF;
	dp[0][2] = -INF;
	for (int i=1; i<=n; i++) {
		dp[i][0] = dp[i-1][0] + b[i];
		dp[i][0] = max(dp[i][0], dp[i-1][1] + b[i]);
		dp[i][0] = max(dp[i][0], dp[i-1][2] + b[i]);
		dp[i][1] = dp[i-1][0] + a[i];
		dp[i][2] = dp[i-1][1] + a[i];
	}

	int ans = -INF;
	for (int i=0; i<3; i++) {
		ans = max(ans, dp[n][i]);
	}
	cout << ans << nl;

	return 0;
}
