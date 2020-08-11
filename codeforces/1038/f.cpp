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

	string s;
	cin >> s;
	int m = s.size();

	auto cyclic = [&] (int len) {
		if (len >= m) return true;
		for (int i=len; i<m; i+=len) {
			int l = min(len,m-i);
			if (s.substr(i-len,l) != s.substr(i,l)) {
				return false;
			}
		}
		return true;
	};

	ll dp[n+1];
	for (int i=1; i<=n; i++) {
		if (cyclic(i)) {
			dp[i] = 1LL << max(0,i-m);
			cerr << "cyclic " << i << nl;
		} else {
			dp[i] = 0;
			cerr << "not cyclic " << i << nl;
		}
		for (int j=1; j<i; j++) {
			if (i%j == 0) {
				dp[i] -= dp[j];
			}
		}
		cerr << "dp " << i << " -> " << dp[i] << nl;
	}

	ll ans = 0;
	for (int i=1; i<=n; i++) {
		if (n%i == 0) {
			cerr << i << " -> " << i << " times " << dp[i] << nl;
			ans += i * dp[i];
		}
	}
	cout << ans << nl;

	return 0;
}
