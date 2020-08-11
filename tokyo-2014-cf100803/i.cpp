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

const int N = 150+1;
int addr[N], adds[N], suff[N];
ll dp[N][N][2];

ll solve(const int n, int id, int score, int move) {
	if (score < 0) return INFLL;
	if (dp[id][score][move] != INFLL) return dp[id][score][move];

	ll res;
	if (move == 0) {
		if (score == 0) return -INFLL;
		if (id == n) return INFLL;
		res = INFLL;
		// take current
		res = min(res, solve(n, id+1, score-adds[id], !move) - addr[id]);
		// force opponent to take current
		res = min(res, max(1LL, solve(n, id+1, score, move) + addr[id] + 1));
	}
	else {
		if (score == suff[id]) return INFLL;
		if (id == n) return -INFLL;
		res = -INFLL;
		// take current
		res = max(res, solve(n, id+1, score, !move) + addr[id]);
		// force opponent to take current
		res = max(res, min(-1LL, solve(n, id+1, score, move) - addr[id] - 1));
	}

	return dp[id][score][move] = res;
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

	memset(dp, INF, sizeof dp);

	int n, a, b;
	cin >> n >> a >> b;

	int sum = 0;
	for (int i=0; i<n; i++) {
		cin >> addr[i] >> adds[i];
		sum += adds[i];
	}
	suff[n] = 0;
	for (int i=n-1; i>=0; i--) {
		suff[i] = suff[i+1] + adds[i];
	}

	int ans = 0;
	for (int s=0; s<=sum; s++) {
		if (solve(n,0,s,0) <= a-b) {
			ans = s;
		}
	}
	cout << ans << " " << sum-ans << nl;

#define DEBUG
#ifdef DEBUG
	cerr << " --------------------- " << nl;
	for (int i=0; i<n; i++) {
		for (int j=0; j<=sum; j++) {
			cerr << i << ',' << j << ": ";
			cerr << solve(n,i,j,0) << " , " << solve(n,i,j,1) << nl;
		}
	}
#endif

	return 0;
}
