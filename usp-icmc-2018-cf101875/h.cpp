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
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	string s;
	cin >> s;
	reverse(s.begin(), s.end());
	while (s.size()%4 != 0) {
		s.push_back('0');
	}

	vector<int> v;
	for (int i=0; i<n; i+=4) {
		int cur = 0;
		for (int j=0; j<4; j++) {
			cur |= ((s[i+j]-'0')%2)<<j;
		}
		cerr << bitset<4>(cur);
		v.push_back(cur);
	}
	cerr << nl;

	n = v.size();
	// 1010, 1100 1001
	int dp[n+1][n+1][n+1][n+1];
	memset(dp, INF, sizeof dp);
	dp[0][0][0][0] = 0;
	for (int t=1; t<=n; t++) {
		int it = v[t-1];
		for (int i=n; i>=0; i--) {
			for (int j=n; j>=0; j--) {
				for (int k=n; k>=0; k--) {
					{ // 1111 0000
						int res = min(__builtin_popcount(0b1111^it), __builtin_popcount(0b0000^it));
						dp[t][i][j][k] = min(dp[t][i][j][k], dp[t-1][i][j][k] + res);
					}
					if (i>0) {
						int res = min(__builtin_popcount(0b0101^it), __builtin_popcount(0b1010^it));
						dp[t][i][j][k] = min(dp[t][i][j][k], dp[t-1][i-1][j][k] + res);
					}
					if (j>0) {
						int res = min(__builtin_popcount(0b1001^it), __builtin_popcount(0b0110^it));
						dp[t][i][j][k] = min(dp[t][i][j][k], dp[t-1][i][j-1][k] + res);
					}
					if (k>0) {
						int res = min(__builtin_popcount(0b0011^it), __builtin_popcount(0b1100^it));
						dp[t][i][j][k] = min(dp[t][i][j][k], dp[t-1][i][j][k-1] + res);
					}
				}
			}
		}
	}

	for (int i=0; i<=n; i+=2) {
		for (int j=0; j<=n; j+=2) {
			for (int k=0; k<=n; k+=2) {
				if (0 < dp[n][i][j][k] && dp[n][i][j][k] < 4) {
					cout << "TATA" << nl;
					return 0;
				}
			}
		}
	}
	cout << "TYNATI" << nl;

	return 0;
}
