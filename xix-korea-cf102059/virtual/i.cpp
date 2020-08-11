#include <bits/stdc++.h>
using namespace std;

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
const int N = 5050;

int dp[N];

int solve(int n) {
	if (n <= 1) return 0;
	if (dp[n] != -1) return dp[n];
	bitset<N> b;
	for (int i = 1; i < n; i++) {
		b[solve(i-1) ^ solve(n - i - 1)] = 1;
	}
	int mex = 0;
	while (b[mex]) mex++;
	return dp[n] = mex;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	/*
	memset(dp, -1, sizeof dp);
	for (int i = 0; i < 1000; i++) {
		assert(solve(i) == grundy(i));
		//cout << solve(i) << " ";
	}
	cout << nl;*/
	memset(dp, -1, sizeof dp);
	int T; cin >> T;
	while (T--) {
		int n; cin >> n;
		puts(solve(n) ? "First" : "Second");
	}

	return 0;
}
