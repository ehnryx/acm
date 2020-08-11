#include <bits/stdc++.h>
using namespace std;

#define debug

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
const ll MOD = 1e9+7;
const int INF = 0x7f7f7f7f;
const ll INFLL = 0x7f7f7f7f7f7f7f7f;

ll count (int bm, int n, int m, int k, const vector<pair<int,int>>& bombs) {
	int left, right, up, down;
	up = right = 0;
	left = down = INF;
	for (int i = 0; i < bombs.size(); i++) {
		if (bm & (1<<i)) {
			right = max(right, bombs[i].first);
			left = min(left, bombs[i].first);
			up = max(up, bombs[i].second);
			down = min(down, bombs[i].second);
		}
	}
	//cerr << "left right up down: " << left << " " << right << " " << up << " " << down << endl;
	return 1LL*(m-up+1)*(down)*(n-right+1)*(left);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<pair<int,int>> bombs;
	ll bad;
	int n, m, k;
	int x, y;
	int T;
	cin >> T;
	while (T--) {
		bombs.clear();
		cin >> n >> m >> k;
		for (int i = 0; i < k; i++) {
			cin >> x >> y;
			bombs.push_back(pair<int,int>(x,y));
		}
		bad = 0;
		for (int bm = 1; bm < 1<<k; bm++) {
			if (__builtin_popcount(bm)%2 == 1)
				bad += count(bm, n, m, k, bombs);
			else
				bad -= count(bm, n, m, k, bombs);
		}
		//cerr << "bad: " << bad << endl;
		cout << 1LL*(n*(n+1)/2)*(m*(m+1)/2) - bad << endl;
	}

	return 0;
}
