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

	int n;
	int colour[200000];
	int dp[200000];
	int last[200001];

	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> colour[i];
		}
		memset(last, -1, sizeof(last));
		dp[0] = 0;
		last[colour[0]] = 0;
		for (int i = 1; i < n; i++) {
			dp[i] = dp[i-1] + 1;
			if (last[colour[i]] != -1)
				dp[i] = min(dp[i], dp[last[colour[i]]]+1);
			last[colour[i]] = i;
		}
		cout << dp[n-1] << nl;
	}

	return 0;
}
