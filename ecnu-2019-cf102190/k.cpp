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

const int N = 101+1;
int dp[N][3][2][2][2]; // carry, done, done
vector<int> ans1, ans2, ans3;

bool solve(const string& s, int n, int c, int d, int e, int f = 0) {
	if (n<0) return c == 0;
	if (dp[n][c][d][e][f] != -1) return dp[n][c][d][e][f];

	{
		int r = s[n]-'0'-c;
		if (r == 0 && solve(s, n-1, 0, 1, 1, 1)) {
			return true;
		}
	}

	// d && e
	if (!f) {
		int r = s[n]-'0'-c;
		if (1 < 10+r && 10+r < 10 && solve(s, n-1, 1, 1, 1)) {
			ans1.push_back(10+r);
			return true;
		}
		if (1 < r && solve(s, n-1, 0, 1, 1)) {
			ans1.push_back(r);
			return true;
		}
	}

	// e
	if (!d && !f) {
		for (int i=2; i<=9; i++) {
			int r = s[n]-'0'-c-i;
			if (1 < 20+r && 20+r < 10 && solve(s, n-1, 2, 0, 1)) {
				ans1.push_back(i);
				ans2.push_back(20+r);
				return true;
			}
			if (1 < 10+r && 10+r < 10 && solve(s, n-1, 1, 0, 1)) {
				ans1.push_back(i);
				ans2.push_back(10+r);
				return true;
			}
			if (1 < r && solve(s, n-1, 0, 0, 1)) {
				ans1.push_back(i);
				ans2.push_back(r);
				return true;
			}
		}
	}

	if (!d && !e && !f) {
		for (int i=2; i<=9; i++) {
			for (int j=2; j<=9; j++) {
				int r = s[n]-'0'-c-i-j;
				if (1 < 20+r && 20+r < 10 && solve(s, n-1, 2, 0, 0)) {
					ans1.push_back(i);
					ans2.push_back(20+r);
					ans3.push_back(j);
					return true;
				}
				if (1 < 10+r && 10+r < 10 && solve(s, n-1, 1, 0, 0)) {
					ans1.push_back(i);
					ans2.push_back(10+r);
					ans3.push_back(j);
					return true;
				}
				if (1 < r && solve(s, n-1, 0, 0, 0)) {
					ans1.push_back(i);
					ans2.push_back(r);
					ans3.push_back(j);
					return true;
				}
			}
		}
	}

	return dp[n][c][d][e][f] = false;
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

	int T;
	cin >> T;

	while (T--) {
		string s;
		cin >> s;
		int n = s.size();
		ans1.clear();
		ans2.clear();
		ans3.clear();
		memset(dp, -1, sizeof dp);
		assert(solve(s,n-1,0,0,0));
		if (ans3.empty()) {
			cout << 2 << nl;
			for (int it : ans1) { cout << it; } cout << " ";
			for (int it : ans2) { cout << it; } cout << nl;
		} else {
			cout << 3 << nl;
			for (int it : ans1) { cout << it; } cout << " ";
			for (int it : ans2) { cout << it; } cout << " ";
			for (int it : ans3) { cout << it; } cout << nl;
		}
	}

	return 0;
}
