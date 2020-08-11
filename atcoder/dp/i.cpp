#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(17);

	int n;
	cin >> n;

	ld p[n+1];
	FOR(i,1,n) {
		cin >> p[i];
	}

	ld dp[n+1][n/2+1];
	fill(dp[0], dp[0]+n/2+1, 0);
	dp[0][0] = 1;
	FOR(i,1,n) {
		For(j,n/2+1) {
			dp[i][j] = dp[i-1][j] * p[i];
			if (j>0) dp[i][j] += dp[i-1][j-1] * (1-p[i]);
		}
	}

	ld ans = 0;
	For(j,n/2+1) {
		ans += dp[n][j];
	}
	cout << ans << nl;

	return 0;
}
