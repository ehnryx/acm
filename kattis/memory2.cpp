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
const ld EPS = 1e-4200L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3+1;

ld dp[N][N];
ld solve(int n, int k, ld pb=1) {
	if (n==0) return 0;
	if (pb < EPS) return 1;
	if (dp[n][k] > -1) return dp[n][k];

	ld res = 0;
	// flip unknown
	if (n>k) {
		ld p1 = (ld)2*(n-k)/(2*n-k);
		// random match!!
		{
			ld p2 = (ld)1/(2*n-k-1);
			res += p1*p2 * solve(n-1, k, p1*p2*pb);
		}
		// flip unknown
		if (n-k>1) {
			ld p2 = (ld)2*(n-k-1)/(2*n-k-1);
			// now we have two knowns
			res += p1*p2 * solve(n, k+2, p1*p2*pb);
		}
		// flip known, match it!
		{
			ld p2 = (ld)k/(2*n-k-1);
			res += p1*p2 * (solve(n-1, k, p1*p2*pb) + 1);
		}
	}
	// flip known
	{
		ld p1 = (ld)k/(2*n-k);
		// match it!
		res += p1 * solve(n-1, k-1, p1*pb);
	}

	return dp[n][k] = res+1;
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

	int n;
	cin >> n;
	fill(&dp[0][0], &dp[0][0]+N*N, -2);
	cout << solve(n, 0) << nl;

	return 0;
}
