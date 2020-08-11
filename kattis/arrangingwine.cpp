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

	int dp[11][n*11+1];
	memset(dp, 0, sizeof dp);

	dp[0][0] = 1;
	for (int i=1; i<=10; i++) {
		for (int j=1; j<=i*n; j++) {
			for (int k=max(0,j-n); k<j; k++) {
				dp[i][j] += dp[i-1][k];
			}
		}
	}

	for (int i=0; i<=10; i++) {
		for (int j=i; j<=i*n; j++) {
			cout << dp[i][j] << "  ";
		}
		cout << nl;
	}

/*
	int r, w, d;
	cin >> r >> w >> d;

	for (int i=1; i<=r; i++) {
	}
	*/

	return 0;
}
