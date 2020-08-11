//
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

// find x,y such that ax+by=gcd(a,b)
ll egcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll d = egcd(b, a%b, y, x);
	y -= x*(a/b);
	return d;
}

ll inverse(ll n) {
	ll x, y;
	egcd(n, MOD, x, y);
	return (x+MOD) % MOD;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);
	
	ll ans;
	int n, x;
	int dice[14][6];
	map<ll,ll> cnt[16];

	int T;
	cin >> T;
	while (T--) {
		cin >> n >> x;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++)
				cin >> dice[i][j];
		}

		for (int i = 0; i <= n+1; i++) 
			cnt[i].clear();
		cnt[0].insert(pair<ll,ll>(1,1));
		cnt[n+1].insert(pair<ll,ll>(x,1));

		for (int i = 0; i < n/2; i++) {
			for (auto& val : cnt[i]) {
				for (int j = 0; j < 6; j++) {
					cnt[i+1][(val.first*dice[i][j])%MOD] += val.second;
				}
			}
		}
		for (int i = n; i > n/2; i--) {
			for (auto& val : cnt[i+1]) {
				for (int j = 0; j < 6; j++) {
					cnt[i][(val.first*inverse(dice[i-1][j]))%MOD] += val.second;
				}
			}
		}

		ans = 0;
		for (auto& point : cnt[n/2]) {
			ans += point.second * cnt[n/2+1][point.first];
		}
		cout << ans << nl;
	}

	return 0;
}
