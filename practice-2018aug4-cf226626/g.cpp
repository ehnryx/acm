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

#define d adj
#define stra

const int N = 60+1;
int adj[N][N][N]; // car, s, t
int dp[N][N][N]; // changes, s, t

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m, r;
	cin >> n >> m >> r;

	// input
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				cin >> d[i][j][k]stra; // sad
			}
		}
	}

	// apsp
	for (int t = 1; t <= m; t++) {
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					adj[t][i][j] = min(adj[t][i][j], adj[t][i][k] + adj[t][k][j]);
				}
			}
		}
	}

	// initialize dp
	memset(dp, INF, sizeof dp);
	for (int t = 1; t <= m; t++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dp[0][i][j] = min(dp[0][i][j], adj[t][i][j]);
			}
		}
	}

	// dp transitions
	for (int c = 1; c <= n; c++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 1; k <= n; k++) {
					dp[c][i][j] = min(dp[c][i][j], dp[c-1][i][k] + dp[0][k][j]);
				}
			}
		}
	}

	// queries
	while (r--) {
		int s, t, k;
		cin >> s >> t >> k;
		int ans = INF;
		for (int i = 0; i <= min(n,k); i++) {
			ans = min(ans, dp[i][s][t]);
		}
		cout << ans << nl;
	}

	return 0;
}
