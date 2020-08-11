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

const int N = 1e7+1;
ld dp[N];
ld pref[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= k; i++) {
		dp[i] = 1;
		pref[i] = pref[i-1] + dp[i];
	}

	for (int i = k+1; i <= n; i++) {
		dp[i] = (pref[i-1] - pref[i-k-1]) / i;
		pref[i] = pref[i-1] + dp[i];
	}

	cout << dp[n] << nl;

	return 0;
}
