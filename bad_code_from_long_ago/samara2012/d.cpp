#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

ll dp[1000001];
ll solve(int n, const vector<int>& factors) {
	if (n == 1) return 1;
	if (dp[n] != -1)
		return dp[n];
	dp[n] = 0;
	for (int f: factors) {
		if (f > n) break;
		if (n % f == 0)
			dp[n] += solve(n/f, factors);
	}
	return dp[n];
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	vector<int> factors;
	int n;
	cin >> n;
	for (int i = 2; i <= n; i++)
		if (n % i == 0)
			factors.push_back(i);
	memset(dp, -1, sizeof(dp));
	cout << solve(n, factors) << nl;
 
	return 0;
}
