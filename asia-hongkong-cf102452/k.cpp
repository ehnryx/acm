#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'

const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const int N = 800 + 1;
int d[N]; int dir[N];
vector<int> lvals[N], rvals[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;
	for(int i=1; i<n; i++) {
		cin >> d[i];
	}
	for(int i=0; i<m; i++) {
		int x, c;
		cin >> x >> c;
		lvals[x].push_back(c);
	}
	for(int i=0; i<m; i++) {
		int x, c;
		cin >> x >> c;
		rvals[x].push_back(c);
	}
	for(int i=1; i<=n; i++) {
		sort(lvals[i].begin(), lvals[i].end(), greater<int>());
		sort(rvals[i].begin(), rvals[i].end(), greater<int>());
	}

	ll ans = 0;
	for(int z=0; z<m; z++) {
		ll res = INFLL;
		pair<int,int> mat;
		pair<ll,int> left(INFLL, 0);
		ll dist = 0;

		for(int i=1; i<=n; i++) {
			if(!lvals[i].empty()) {
				left = min(left, make_pair(lvals[i].back() - dist, i));
			}
			if(!rvals[i].empty()) {
				auto [val, j] = left;
				ll cur = val + dist + rvals[i].back();
				if(cur < res) {
					res = cur;
					mat = make_pair(j, i);
				}
			}
			if(dir[i] < 0) {
				dist -= d[i];
			} else {
				dist += d[i];
			}
		}

		left = make_pair(INFLL, 0);
		dist = 0;
		for(int i=n; i>=1; i--) {
			if(!lvals[i].empty()) {
				left = min(left, make_pair(lvals[i].back() - dist, i));
			}
			if(!rvals[i].empty()) {
				auto [val, j] = left;
				ll cur = val + dist + rvals[i].back();
				if(cur < res) {
					res = cur;
					mat = make_pair(j, i);
				}
			}
			if(dir[i-1] > 0) {
				dist -= d[i-1];
			} else {
				dist += d[i-1];
			}
		}

		auto [s, t] = mat;
		lvals[s].pop_back();
		rvals[t].pop_back();
		if(s<t) {
			for(int i=s; i<t; i++) {
				dir[i]++;
			}
		} else {
			for(int i=s; i>t; i--) {
				dir[i-1]--;
			}
		}
		ans += res;
		cout << ans << nl;
	}

	return 0;
}
