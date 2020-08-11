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

const int N = 1e4+1;
int dp[N][7];

void init() {
	memset(dp, -1, sizeof dp);
}

int solve(int n, int f=1) {
	if (n < 0) return INF;
	if (n == 0) return 0;
	if (dp[n][f] != -1) return dp[n][f];

	int res = INF;
	for (int i=1; i<=6; i++) {
		if (i == f || i+f == 7) continue;
		res = min(res, solve(n-i, i) + 1);
	}

	return dp[n][f] = res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		cout << (solve(n)==INF ? -1 : solve(n)) << nl;
	}

	return 0;
}
