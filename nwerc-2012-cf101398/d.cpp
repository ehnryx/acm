#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const vector<int> t = {1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7};
const vector<int> segs = {
	t[0] + t[1] + t[2] + t[3] + t[4] + t[5],
	t[1] + t[2],
	t[0] + t[1] + t[3] + t[4] + t[6],
	t[0] + t[1] + t[2] + t[3] + t[6],
	t[1] + t[2] + t[5] + t[6],
	t[0] + t[2] + t[3] + t[5] + t[6],
	t[0] + t[2] + t[3] + t[4] + t[5] + t[6],
	t[0] + t[1] + t[2],
	t[0] + t[1] + t[2] + t[3] + t[4] + t[5] + t[6],
	t[0] + t[1] + t[2] + t[3] + t[5] + t[6]
};

int broken[4][7];

bool check(int h1, int h1d, int x) {
	for (int bit = 0; bit < 7; bit++) {
		if (segs[h1d] & (1 << bit)) {
			if (broken[x][bit] == 1) return 0;
			broken[x][bit] = 0;
		}
		if ((segs[h1] & (1 <<bit)) == (segs[h1d] & (1 << bit))) {
			continue;
		}
		if ((segs[h1] & (1 << bit)) && !(segs[h1d] & (1 << bit))) {
			if (broken[x][bit] == 0) return 0;
			broken[x][bit] = 1;
		}
		if (!(segs[h1] & (1 << bit)) && (segs[h1d] & (1 << bit))) {
			return 0;
		}
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	while (cin >> n) {
		vector<pair<int, int>> dumb(n);
		char c;
		for (int i = 0; i < n; i++) {
			cin >> dumb[i].first >> c >> dumb[i].second;
		}
		vector<pair<int, int>> ans;
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 60; j++) {
				int h = i, m = j;
				memset(broken, -1, sizeof broken);
				for (const auto& p : dumb) {
					int h1 = h / 10, h2 = h % 10;
					int h1d = p.first / 10, h2d = p.first % 10;
					int m1 = m / 10, m2 = m % 10;
					int m1d = p.second / 10, m2d = p.second % 10;
					if (!check(h1, h1d, 0)) goto bad;
					if (!check(h2, h2d, 1)) goto bad;
					if (!check(m1, m1d, 2)) goto bad;
					if (!check(m2, m2d, 3)) goto bad;
					m = (m+1) % 60;
					if (m == 0) {
						h = (h+1) % 24;
					}
				}
				ans.push_back({i, j});
bad:;
			}
		}
		if (ans.empty()) {
			cout << "none" << nl;
		} else {
			for (const auto& p : ans) {
				cout << setw(2) << setfill('0') << p.first << ":" << setw(2) << setfill('0') << p.second << " ";
			}
			cout << nl;
		}
	}

	return 0;
}
