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

ll t(int k, vector<pair<int, int>>& v) {
	ll ans = 0;
	int curlet = 0;
	for (auto p : v) {
		p.second -= curlet;
		if (p.second < 0) {
			curlet = -p.second;
			continue;
		}
		ans += 2LL * p.first * (p.second / k);
		p.second %= k;
		if (p.second) {
			ans += 2LL * p.first;
			curlet = k - p.second;
		} else curlet = 0;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n, k; cin >> n >> k;
	vector<pair<int, int>> pos, neg;
	for (int i = 0; i < n; i++) {
		int x, m; cin >> x >> m;
		if (x >= 0) pos.push_back({x, m});
		else neg.push_back({-x, m});
	}
	sort(pos.begin(), pos.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
			return a.first > b.first;
		});
	sort(neg.begin(), neg.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
			return a.first > b.first;
		});
	cout << t(k, pos) + t(k, neg) << endl;

	return 0;
}
