#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
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

const int N = 1e6+1;
ld dp[N][2];

ld solve(int n, bool has) {
	if (dp[n][has] > -1) return dp[n][has];
	if (n == 0) return dp[n][has] = 1-has;
	if (has) return dp[n][has] = 1-solve(n-1, false);
	else return dp[n][has] = (n+1 - n*solve(n-1, true)) / (n+2);
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(13);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	fill(&dp[0][0], &dp[0][0]+N*2, -2);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		string s, t;
		cin >> s;
		cin >> t;

		int cnt = 0;
		int old = -1;
		For(i,n) {
			if (s[i]+t[i]-2*'0' == 1) {
				old = (s[i]=='1');
			} else if (s[i]=='1' && t[i]=='1') {
				cnt++;
			}
		}
		cout << solve(cnt, old) << nl;
	}

	return 0;
}
