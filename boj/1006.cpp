//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e4 + 1;
int a[N], b[N];

int dp[N][4];
// 00, 01, 10, 11; 0 means taken

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while(T--) {

		int n, w;
		cin >> n >> w;
		for(int i=1; i<=n; i++) {
			cin >> a[i];
		}
		for(int i=1; i<=n; i++) {
			cin >> b[i];
		}
		a[0] = b[0] = INF;

		int ans = 2*n;

		memset(dp, INF, sizeof dp);
		dp[0][0] = 0;
		for(int i=1; i<=n; i++) {
			dp[i][0b11] = dp[i-1][0];
			dp[i][0b10] = dp[i][0b11] + 1;
			dp[i][0b01] = dp[i][0b11] + 1;
			if(a[i] + a[i-1] <= w) dp[i][0b01] = min(dp[i][0b01], dp[i-1][0b10] + 1);
			if(b[i] + b[i-1] <= w) dp[i][0b10] = min(dp[i][0b10], dp[i-1][0b01] + 1);
			dp[i][0] = min(dp[i][0b10] + 1, dp[i][0b01] + 1);
			if(a[i] + b[i] <= w) dp[i][0] = min(dp[i][0], dp[i-1][0] + 1);
			if(a[i] + a[i-1] <= w && b[i] + b[i-1] <= w) {
				dp[i][0] = min(dp[i][0], dp[i-1][0b11] + 2);
			}
		}
		ans = min(ans, dp[n][0]);

		if(a[1] + a[n] <= w) {
			memset(dp, INF, sizeof dp);
			dp[0][0b10] = 0;
			a[0] = a[n];
			for(int i=1; i<=n; i++) {
				dp[i][0b11] = dp[i-1][0];
				dp[i][0b10] = dp[i][0b11] + 1;
				dp[i][0b01] = dp[i][0b11] + 1;
				if(a[i] + a[i-1] <= w) dp[i][0b01] = min(dp[i][0b01], dp[i-1][0b10] + 1);
				if(b[i] + b[i-1] <= w) dp[i][0b10] = min(dp[i][0b10], dp[i-1][0b01] + 1);
				dp[i][0] = min(dp[i][0b10] + 1, dp[i][0b01] + 1);
				if(a[i] + b[i] <= w) dp[i][0] = min(dp[i][0], dp[i-1][0] + 1);
				if(a[i] + a[i-1] <= w && b[i] + b[i-1] <= w) {
					dp[i][0] = min(dp[i][0], dp[i-1][0b11] + 2);
				}
			}
			a[0] = INF;
			ans = min(ans, dp[n][0b10]);
		}

		if(b[1] + b[n] <= w) {
			memset(dp, INF, sizeof dp);
			dp[0][0b01] = 0;
			b[0] = b[n];
			for(int i=1; i<=n; i++) {
				dp[i][0b11] = dp[i-1][0];
				dp[i][0b10] = dp[i][0b11] + 1;
				dp[i][0b01] = dp[i][0b11] + 1;
				if(a[i] + a[i-1] <= w) dp[i][0b01] = min(dp[i][0b01], dp[i-1][0b10] + 1);
				if(b[i] + b[i-1] <= w) dp[i][0b10] = min(dp[i][0b10], dp[i-1][0b01] + 1);
				dp[i][0] = min(dp[i][0b10] + 1, dp[i][0b01] + 1);
				if(a[i] + b[i] <= w) dp[i][0] = min(dp[i][0], dp[i-1][0] + 1);
				if(a[i] + a[i-1] <= w && b[i] + b[i-1] <= w) {
					dp[i][0] = min(dp[i][0], dp[i-1][0b11] + 2);
				}
			}
			b[0] = INF;
			ans = min(ans, dp[n][0b01]);
		}

		if(a[1] + a[n] <= w && b[1] + b[n] <= w) {
			memset(dp, INF, sizeof dp);
			dp[0][0b11] = 0;
			a[0] = a[n];
			b[0] = b[n];
			for(int i=1; i<=n; i++) {
				dp[i][0b11] = dp[i-1][0];
				dp[i][0b10] = dp[i][0b11] + 1;
				dp[i][0b01] = dp[i][0b11] + 1;
				if(a[i] + a[i-1] <= w) dp[i][0b01] = min(dp[i][0b01], dp[i-1][0b10] + 1);
				if(b[i] + b[i-1] <= w) dp[i][0b10] = min(dp[i][0b10], dp[i-1][0b01] + 1);
				dp[i][0] = min(dp[i][0b10] + 1, dp[i][0b01] + 1);
				if(a[i] + b[i] <= w) dp[i][0] = min(dp[i][0], dp[i-1][0] + 1);
				if(a[i] + a[i-1] <= w && b[i] + b[i-1] <= w) {
					dp[i][0] = min(dp[i][0], dp[i-1][0b11] + 2);
				}
			}
			ans = min(ans, dp[n][0b11]);
		}

		cout << ans << nl;

	}

	return 0;
}
