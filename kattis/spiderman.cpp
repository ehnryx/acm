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

const int N = 40+1;
const int M = 1e3+1;
int dp[N][M], pre[N][M];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int T;
	cin >> T;
	while (T--) {
		int n, a;
		cin >> n;

		memset(dp, INF, sizeof dp);
		dp[0][0] = 0;
		for (int i=1; i<=n; i++) {
			cin >> a;
			for (int j=0; j+a<M; j++) {
				if (max(dp[i-1][j],j+a) < dp[i][j+a]) {
					dp[i][j+a] = max(dp[i-1][j],j+a);
					pre[i][j+a] = j;
				}
			}
			for (int j=a; j<M; j++) {
				if (max(dp[i-1][j],j-a) < dp[i][j-a]) {
					dp[i][j-a] = max(dp[i-1][j],j-a);
					pre[i][j-a] = j;
				}
			}
		}

		if (dp[n][0] == INF) {
			cout << "IMPOSSIBLE" << nl;
		} else {
			vector<char> ans;
			int pos = 0;
			for (int i=n; i>0; i--) {
				int nxt = pre[i][pos];
				if (pos>nxt) ans.push_back('U');
				else ans.push_back('D');
				pos = nxt;
			}
			reverse(ans.begin(), ans.end());
			for (char c : ans) {
				cout << c;
			}
			cout << nl;
		}
	}

	return 0;
}
