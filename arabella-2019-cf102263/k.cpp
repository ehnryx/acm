#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ll CAP = 1e17;

const int N = 100+1;
ll dp[2][N*N/2][4]; // pos, cnt, type

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m, x;
	cin >> n >> m >> x;

	if (x > (n*m+1)/2) {
		cout << 0 << nl;
		return 0;
	}

	dp[0][0][3] = 1;
	int id = 0;
	for (int d=n+m-1; d>=1+1; d--) {
		bool first = true;
		for (int j=1; j<=m; j++) {
			int i = d-j;
			if (1<=i && i<=n) {
				id ^= 1;
				//cerr << " @ " << i << ',' << j << nl;
				memset(dp[id], 0, sizeof dp[id]);
				if (first) {
					first = false;
					for (int c=0; c<=x; c++) {
						if (c>0 && (i<n||j==1) && (j<m||i==1)) {
							ll sum0 = dp[id^1][c-1][0] + dp[id^1][c-1][1] + dp[id^1][c-1][2] + dp[id^1][c-1][3];
							if (sum0 > CAP) sum0 %= MOD;
							dp[id][c][0] = sum0;
						}
						ll sum1 = dp[id^1][c][0] + dp[id^1][c][1] + dp[id^1][c][2] + dp[id^1][c][3];
						if (sum1 > CAP) sum1 %= MOD;
						if (i>1 && (i<n||j==1)) dp[id][c][1] = sum1;
						if (j>1 && (j<m||i==1)) dp[id][c][2] = sum1;
						if (i>1 && j>1) dp[id][c][3] = sum1;
					}
				} else {
					for (int c=0; c<=x; c++) {
						if (c>0 && (i<n||j==1) && (j<m||i==1)) {
							ll sum0 = dp[id^1][c-1][1] + dp[id^1][c-1][3];
							if (sum0 > CAP) sum0 %= MOD;
							dp[id][c][0] = sum0;
						}
						if (i>1 && (i<n||j==1)) {
							dp[id][c][1] = dp[id^1][c][1] + dp[id^1][c][3];
							if (dp[id][c][1] > CAP) dp[id][c][1] %= MOD;
						}
						if (j>1 && (j<m||i==1)) {
							dp[id][c][2] = dp[id^1][c][2] + dp[id^1][c][0];
							if (dp[id][c][2] > CAP) dp[id][c][2] %= MOD;
						}
						if (i>1 && j>1) {
							dp[id][c][3] = dp[id^1][c][0] + dp[id^1][c][2];
							if (dp[id][c][3] > CAP) dp[id][c][3] %= MOD;
						}
					}
				}
				//cerr << "dp " << 0 << " -> " << dp[id][0][0] << ',' << dp[id][0][1] << ',' << dp[id][0][2] << ',' << dp[id][0][3] << nl;
				//cerr << "dp " << 1 << " -> " << dp[id][1][0] << ',' << dp[id][1][1] << ',' << dp[id][1][2] << ',' << dp[id][1][3] << nl;
				//cerr << "dp " << 2 << " -> " << dp[id][2][0] << ',' << dp[id][2][1] << ',' << dp[id][2][2] << ',' << dp[id][2][3] << nl;
				//cerr << "dp " << 3 << " -> " << dp[id][3][0] << ',' << dp[id][3][1] << ',' << dp[id][3][2] << ',' << dp[id][3][3] << nl;
			}
		}
	}

	cout << dp[id][x][0] % MOD << nl;

	return 0;
}
