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
const int N = 1e5+10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int n;
int l[N], r[N], f[N];
int dp[N][2][2];

inline bool nand(int a, int b) {
	return !(a && b);
}
int solve(int cur, bool expect, bool actual) {
	if (cur == -1) {
		return (expect == actual);
	}
	if (dp[cur][expect][actual] != -1) {
		return dp[cur][expect][actual];
	}
	ll ans = 0;
	if (f[cur] == -1) {
		for (int x1 = 0; x1 <= 1; x1++) {
			for (int x2 = 0; x2 <= 1; x2++) {
				for (int y1 = 0; y1 <= 1; y1++) {
					for (int y2 = 0; y2 <= 1; y2++) {
						if (nand(x1, x2) != expect || nand(y1, y2) != actual) continue;
						ans += (ll) solve(l[cur], x1, y1) * solve(r[cur], x2, y2);
						ans %= MOD;
					}
				}
			}
		}
	} else {
		if (actual != f[cur]) {
			return dp[cur][expect][actual] = 0;
		}
		for (int x1 = 0; x1 <= 1; x1++) {
			for (int x2 = 0; x2 <= 1; x2++) {
				for (int y1 = 0; y1 <= 1; y1++) {
					for (int y2 = 0; y2 <= 1; y2++) {
						if (nand(x1, x2) != expect) continue;
						ans += (ll) solve(l[cur], x1, y1) * solve(r[cur], x2, y2);
						ans %= MOD;
					}
				}
			}
		}
	}
	return dp[cur][expect][actual] = ans;
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

	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y >> f[i]; x--; y--;
		l[i] = x; r[i] = y;
	}
	memset(dp, -1, sizeof dp);
	cout << (solve(0, 0, 1) + solve(0, 1, 0)) % MOD << endl;

	return 0;
}
