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

const int N = 1e5+1;
int cost[N];
unordered_map<string,ll> dp[N];

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

	for (int i = 1; i <= n; i++) {
		cin >> cost[i];
	}

	dp[0]["!"] = 0;
	for (int i = 1; i <= n; i++) {
		string s, t;
		cin >> s;
		t = s;

		dp[i][s] = INFLL;
		for (const pair<string,ll>& it : dp[i-1]) {
			if (it.first <= s) {
				dp[i][s] = min(dp[i][s], it.second);
			}
		}

		reverse(s.begin(), s.end());
		if (s != t) {
			dp[i][s] = INFLL;
			for (const pair<string,ll>& it : dp[i-1]) {
				if (it.first <= s) {
					dp[i][s] = min(dp[i][s], it.second + cost[i]);
				}
			}
		}
	}

	ll ans = INFLL;
	for (const pair<string,ll>& it : dp[n]) {
		ans = min(ans, it.second);
	}

	if (ans == INFLL) {
		cout << -1 << nl;
	} else {
		cout << ans << nl;
	}

	return 0;
}
