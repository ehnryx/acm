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

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int colo[200001];
	memset(colo, -1, sizeof(colo));
	int n;
	cin >> n;
	int a[n];
	int dp[n];
	memset(dp, INF, sizeof(dp));
	dp[0] = 0;
	cin >> a[0];
	colo[a[0]] = 0;
	for (int i = 1; i < n; i++) {
		cin >> a[i];
		dp[i] = min(dp[i], dp[i-1]+1);
		if (colo[a[i]] != -1) dp[i] = min(dp[i], dp[colo[a[i]]]+1);
		colo[a[i]] = i;
	}
	cout << dp[n-1] << nl;

	return 0;
}
