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

struct House {
	int id, d, m;
	bool operator < (const House& v) const {
		if (d != v.d) return d < v.d;
		if (m != v.m) return m > v.m;
		else return id < v.id;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n, x, y;
		cin >> n >> x >> y;

		vector<House> houses;
		int d, m;
		for (int i = 1; i <= n; i++) {
			cin >> d >> m;
			if (d <= x && m >= y) {
				houses.push_back({i,d,m});
			}
		}

		if (houses.empty()) {
			cout << -1 << nl;
		} else {
			sort(houses.begin(), houses.end());
			cout << houses[0].id << nl;
		}
	}

	return 0;
}
