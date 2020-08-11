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

const int N = 1e3+1;
int dp[N][N];
bool solve(string& s, int i, int n, int cur) {
	if (i == s.size()) return cur == 0;
	if (dp[i][cur] != -1) return dp[i][cur];

	if (s[i] != '?') {
		dp[i][cur] = solve(s, i+1, n, (cur*10+s[i]-'0')%n);
		return dp[i][cur];
	}
	else {
		if (i > 0) {
			s[i] = '0';
			if (solve(s, i+1, n, (cur*10)%n)) {
				return true;
			}
		}
		for (int d=1; d<10; d++) {
			s[i] = d+'0';
			if (solve(s, i+1, n, (cur*10+d)%n)) {
				return true;
			}
		}
	}
	s[i] = '?';
	dp[i][cur] = false;
	return dp[i][cur];
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

	memset(dp, -1, sizeof dp);

	string s;
	int n;
	cin >> s >> n;

	if (solve(s,0,n,0)) {
		cout << s << nl;
	} else {
		cout << '*' << nl;
	}

	return 0;
}
