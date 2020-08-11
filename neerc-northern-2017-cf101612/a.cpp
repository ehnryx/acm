#include <bits/stdc++.h>
using namespace std;

#define FILENAME "auxiliary"

typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';

const int N = 1e6+1;
int dp[N];

int cnt[10] = {6,2,5,5,4,5,6,3,7,6};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	if(fopen(FILENAME ".in", "r")) {
		freopen(FILENAME ".in", "r", stdin);
		freopen(FILENAME ".out", "w", stdout);
	}

	int n;
	cin >> n;
	dp[0] = 0;
	for(int i=1; i<=n; i++) {
		dp[i] = -INF;
		for(int d=0; d<=9; d++) {
			if(cnt[d] <= i) {
				dp[i] = max(dp[i], dp[i-cnt[d]] + d);
			}
		}
	}
	cout << dp[n] << nl;

	return 0;
}
