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

int num;
int coins[100];

int grd[2000000];
int greedy(int n, int i) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	if (grd[n] == INF)
		grd[n] = greedy(n % coins[i], i-1) + (n/coins[i]);
	return grd[n];
}

int dp[2000000];
void init() {
	memset(dp, INF, sizeof(dp));
	memset(grd, INF, sizeof(dp));
}
int optimal(int n) {
	if (n == 0) return 0;
	if (n < 0) return INF;
	if (dp[n] == INF) {
		for (int i = 0; i < num; i++)
			dp[n] = min(dp[n], 1 + optimal(n-coins[i]));
	}
	return dp[n];
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	init();

	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> coins[i];
	}
	for (int i = 1; i < coins[num-1] + coins[num-2]; i++) {
		if (greedy(i, num-1) != optimal(i)) {
			cout << "non-canonical" << endl;
			return 0;
		}
	}
	cout << "canonical" << endl;

	return 0;
}
