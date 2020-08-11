//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 200;
const int M = 128;
int dp[N][N][128];
int solve(int l, int r, int c, const string& s) {
	if(l > r) return 0;
	if(dp[l][r][c] != -1) return dp[l][r][c];
	if(s[l] == c) {
		return dp[l][r][c] = 1 + solve(l+1, r, c, s);
	} else if(s[r] == c) {
		return dp[l][r][c] = 1 + solve(l, r-1, c, s);
	} else {
		int res = 2 + min(solve(l, r, s[l], s), solve(l, r, s[r], s));
		for(int i=l; i<r; i++) {
			res = min(res, solve(l, i, c, s) + solve(i+1, r, c, s));
		}
		return dp[l][r][c] = res;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	string s;
	getline(cin, s);
	while(T--) {
		memset(dp, -1, sizeof dp);
		getline(cin, s);
		int n = s.size();
		int ans = 2 + min(solve(0, n-1, s[0], s), solve(0, n-1, s[n-1], s));
		cout << ans << nl;
	}

	return 0;
}
