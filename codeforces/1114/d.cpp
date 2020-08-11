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

const int N = 5e3;
int c[N];

int dp[N][N];
int solve(int l, int r) {
	if (dp[l][r] != -1) return dp[l][r];
	if (l == r) return dp[l][r] = 0;
	int res = 0;
	if (c[l] == c[r]) {
		res = 1 + solve(l+1,r-1);
	} else {
		res = 1 + min(solve(l,r-1), solve(l+1,r));
	}
	return dp[l][r] = res;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	memset(dp, -1, sizeof dp);

	int n;
	cin >> n;

	int m=0;
	for (int i=0; i<n; i++) {
		cin >> c[m];
		if (m==0 || c[m]!=c[m-1]) m++;
	}

	cout << solve(0,m-1) << nl;

	return 0;
}
