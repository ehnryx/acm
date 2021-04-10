#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';
const int INF = 0x3f3f3f3f;

struct Point {
	int x, t, right;
	bool operator < (const Point& o) const {
		if (x != o.x) return x < o.x;
		return t > o.t;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case #" << tt << ": ";
		vector<Point> p;
		int n, m;
		cin >> n >> m;
		for (int i=0; i<n; i++) {
			int a, b;
			cin >> a >> b;
			p.push_back({a,1,b});
			p.push_back({b,-1});
		}
		for (int i=0; i<m; i++) {
			int v;
			cin >> v;
			p.push_back({v,0});
		}
		sort(p.begin(), p.end());

		int ans = INF;
		multiset<int> active;
		multiset<int> dead;
		for (const Point& it : p) {
			if (it.t == 0) {
				if (active.empty()) {
					ans = 0;
					break;
				} else {
					ans = min(ans, (int)active.size());
					auto jt = active.begin();
					dead.insert(*jt);
					active.erase(jt);
				}
			} else {
				if (it.t == 1) {
					active.insert(it.right);
				} else {
					auto jt = dead.find(it.x);
					if (jt == dead.end()) {
						active.erase(active.find(it.x));
					} else {
						dead.erase(jt);
					}
				}
			}
		}

		ans = n-ans + 1;
		if (ans > n) {
			cout << "IMPOSSIBLE!" << nl;
		} else {
			cout << ans << nl;
		}
	}

	return 0;
}
