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

const int N = 20+1;
const int M = N*600+1;
unordered_set<int> dp[N][M];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	dp[0][0].insert(0);

	for (int n;;) {
		cin >> n;
		if (!n) break;

		int m = 600*(n/2.+1)+1;
		for (int i=1; i<=n; i++) {
			int a;
			cin >> a;
			for (int j=0; j<m; j++) {
				dp[i][j].clear();
			}
			for (int j=0; j<m; j++) {
				for (int k : dp[i-1][j]) {
					if (j+a<m) dp[i][j+a].insert(k);
					if (k+a<m) dp[i][j].insert(k+a);
				}
			}
		}

		int first = INF;
		int second = 0;
		for (int j=0; j<m; j++) {
			for (int k : dp[n][j]) {
				if (j>=k && j-k < first-second) {
					tie(first,second) = tie(j,k);
				}
			}
		}
		cout << first << " " << second << nl;
	}

	return 0;
}
