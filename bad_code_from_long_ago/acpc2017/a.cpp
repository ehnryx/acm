#include <bits/stdc++.h>
using namespace std;
//
//#define debug

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
const ll MOD = 1e9+7;
const int INF = 0x7f7f7f7f;
const ll INFLL = 0x7f7f7f7f7f7f7f7f;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int first, curr;
	ll prev[200001];
	ll ans;
	ll dp[200001][2];
	int n;
	string s;
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		cin >> s;
		dp[0][0] = 0;
		dp[0][1] = 0;
		curr = first = -1;
		for (int i = 0; i < n; i++) {
			if (s[i] == '1') {
				if (first == -1) {
					curr = first = i+1;
					prev[i+1] = 0;
				}
				else {
					prev[i+1] = curr;
					curr = i+1;
				}
				dp[i+1][0] = dp[i][1];
				dp[i+1][1] = dp[i][0] + 1;
			}
			else {
				dp[i+1][0] = dp[i][0] + 1;
				dp[i+1][1] = dp[i][1];
			}	
		}
		//cerr << "dp: " << endl; for (int i = 1; i <= n; i++)
			//cerr << s[i-1] << " : " << i << ",0: " << dp[i][0] << "  ,1: " << dp[i][1] << endl;
		//cerr << "ans: " << endl;
		ans = 0;
		for (int i = 1; i <= n; i++) {
			if (s[i-1] == '0') {
				if (dp[i][1] > 0)
					ans += dp[i][1]-1;
			}
			else {
				ans += dp[i][1]-(i-prev[i]);
			}
			//cerr << "ans after " << i << ": " << ans << endl;
		}
		cout << ans << endl;
	}

	return 0;
}
