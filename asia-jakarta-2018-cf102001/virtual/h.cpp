#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

struct Point {
	int x, t, c;
	bool operator < (const Point& o) const {
		if (x != o.x) return x < o.x;
		return t < o.t;
	}
};

const int N = 1<<17;
int fix[N], val[N], pref[N], memo[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	vector<Point> p;
	for (int i=1; i<=n; i++) {
		cin >> fix[i];
		if (fix[i] == 0) val[i] = 1;
		else val[i] = fix[i];
		pref[i] = pref[i-1] + val[i];
		p.push_back({i,0});
	}
	for (int i=1; i<=k; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		int sum = pref[b] - pref[a-1] - c;
		if (sum < 0) {
			cout << "Impossible" << nl;
			return 0;
		}
		p.push_back({a,-i,sum/2});
		p.push_back({b,i,sum/2});
	}
	sort(p.begin(), p.end());

	int offset = 0;
	multiset<int> active;
	for (const Point& it : p) {
		if (it.t < 0) {
			memo[-it.t] = it.c + offset;
			active.insert(it.c + offset);
		} else if (it.t > 0) {
			active.erase(active.find(memo[it.t]));
		} else { // point 
			if (fix[it.x] == 0 && (active.empty() || *active.begin() > offset)) {
				val[it.x] = -1;
				offset++;
			}
		}
	}

	for (int i=1; i<=n; i++) {
		cout << val[i] << " ";
	}
	cout << nl;

	return 0;
}
