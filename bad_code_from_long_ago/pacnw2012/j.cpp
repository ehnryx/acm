#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;
const int N = 1e6+10;

int h, bot, top;
vector<int> bricks(3);

ll dp[N];
ll solve(ll hgt) {
	if (hgt > h) return -INFLL;
	if (hgt == h) return 0;
	if (dp[hgt] != -1) return dp[hgt];
	ll ans = 0;
	for (int i : bricks) {
		if (hgt + i > h) continue;
		ld topw = (top + (bot - top) * (1 - (ld) (hgt + i) / h));
		if (topw < i) continue;
		ll num = (ll) (topw / i);
		ans = max(ans, solve(hgt + i) + num*num*i*i*i);
	}
	return dp[hgt] = ans;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	while (cin >> h >> bot >> top >> bricks[0] >> bricks[1] >> bricks[2]) {
		memset(dp, -1, sizeof dp);
		cout << solve(0) << endl;
	}

	return 0;
}
