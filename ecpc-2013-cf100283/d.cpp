#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define TESTFILE "rooks"

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

ll power(ll b, int e) {
	ll res = 1;
	for ( ; e>0; e/=2) {
		if (e&1) res = res*b % MOD;
		b = b*b % MOD;
	}
	return res;
}

const int N = 1e3+1;
ll ncr[N][N];
ll dp[N][N];

void solve() {
	int n, m, k;
	cin >> n >> m >> k;

	unordered_set<int> h, v;
	for (int i=0; i<k; i++) {
		int a, b;
		cin >> a >> b;
		h.insert(a);
		v.insert(b);
	}

	if (h.size() < v.size()) swap(n,m);
	int a = min(h.size(), v.size());
	int b = max(h.size(), v.size());
	int minv = b;

	memset(dp, 0, sizeof dp);
	dp[0][a] = 1;
	for (int i=1; i<=b; i++) {
		for (int j=0; j<=a; j++) {
			// fill in
			if (j<a) dp[i][j] = (dp[i][j] + (j+1)*dp[i-1][j+1] % MOD) % MOD;
			// match existing
			dp[i][j] = (dp[i][j] + (a-j)*dp[i-1][j] % MOD) % MOD;
			// put outside
			dp[i][j] = (dp[i][j] + (m-a)*dp[i-1][j] % MOD) % MOD;
			//cerr << "dp " << i << " " << j << " -> " << dp[i][j] << nl;
		}
	}
	cout << minv << " " << dp[b][0] << nl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
	freopen(TESTFILE ".in", "r", stdin);
#endif

	for (int i=0; i<N; i++) {
		ncr[i][0] = ncr[i][i] = 1;
		for (int j=1; j<i; j++) {
			ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % MOD;
		}
	}

	int T;
	cin >> T;

	for (int tt=1; tt<=T; tt++) {
		cout << "Case " << tt << ": ";
		solve();
	}

	return 0;
}
