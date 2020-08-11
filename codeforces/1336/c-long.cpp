//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 3000 + 7;
ll dp[N][N]; // suffix starting at i in s, prefix ending before j in t
ll pf[N][N];

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	string s, t;
	cin >> s >> t;
	int n = s.size();
	int m = t.size();

	dp[n][0] = 1;
	for(int i=n-1; i>=0; i--) {
		dp[i][0] = dp[i+1][0] + 1;
		for(int j=1; j<=m; j++) {
			dp[i][j] = dp[i+1][j];
			if(s[i] == t[j-1]) {
				dp[i][j] = (dp[i][j] + dp[i+1][j-1]) % MOD;
			}
		}
	}

	for(int i=0; i<m; i++) {
		pf[0][i] = (s[0] == t[i]);
	}
	for(int j=1; j<m; j++) {
		for(int i=0; i+j<m; i++) {
			if(s[j] == t[i]) {
				pf[j][i] = (pf[j][i] + pf[j-1][i+1]) % MOD;
			}
			if(s[j] == t[i+j]) {
				pf[j][i] = (pf[j][i] + pf[j-1][i]) % MOD;
			}
		}
	}

	ll ans = pf[m-1][0] * (n-m+1) % MOD;
	//cerr<<"pf[m-1][0] = "<<pf[m-1][0]<<" * "<<(n-m+1)<<nl;
	for(int i=1, k=1; i<n; i++) {
		if(s[i] == t[m-1]) {
			// take + tail
			ans += dp[i+1][m-1] * k % MOD;
			//cerr<<"add @ "<<i<<" -> "<<dp[i+1][m-1]<<" * "<<k<<nl;
		}
		k = 2*k % MOD;
	}
	for(int i=1; i<m; i++) {
		ll cur = pf[i-1][m-i] * dp[i+1][m-i] % MOD;
		ans += cur;
		//cerr<<"@ "<<i<<" -> "<<pf[i-1][m-i]<<" * "<<dp[i+1][m-i]<<" = "<<cur<<nl;
	}
	cout << 2 * ans % MOD << nl;

	return 0;
}
