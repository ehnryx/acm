#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const int K = 301, N = 1e5+1;
const int M = 1e9+7;

int n, k;
string a, b;
int h[26];
int dp[N][K];

int solve(int ai, int bi) {
	if (bi >= k) return 1;
	if (ai >= n) return 0;
	if (dp[ai][bi] != -1) return dp[ai][bi];
	if (a[ai] != b[bi]) return dp[ai][bi] = solve(ai+1, bi);
	return dp[ai][bi] = (solve(ai+h[a[ai]-'A']+1, bi+1) + solve(ai+1, bi)) % M;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> k >> n;
	for (int i = 0; i < 26; i++) {
		cin >> h[i];
	}
	cin >> b >> a;
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0) << nl;
	//for (int i = 0; i < n; i++) { for (int j = 0; j < k; j++) cerr << solve(i, j) << " "; cerr << nl; }

	return 0;
}
