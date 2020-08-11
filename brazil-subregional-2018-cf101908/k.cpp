#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-10;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	ld x, y, r;
	vector<pair<ld,int>> p;
	for (int i=1; i<=n; i++) {
		cin >> x >> y >> r;
		ld lb = abs(sqrt(x*x+y*y)-r)+EPS;
		ld ub = sqrt(x*x+y*y)+r-EPS;
		p.push_back(pair<ld,int>(lb, i));
		p.push_back(pair<ld,int>(ub, -i));
		cerr << x << " " << y << " " << r << " -> " << lb << " " << ub << nl;
	}
	sort(p.begin(), p.end());

	ll ans = 0;
	unordered_set<int> cur, bad;
	for (const auto& it : p) {
		cerr << it.first << " " << it.second << nl;
		int id = abs(it.second);
		if (it.second > 0) {
			ans += cur.size();
			if (!bad.count(id)) {
				cur.insert(id);
			}
		}
		else {
			if (cur.count(id)) {
				cur.erase(id);
			} else {
				bad.insert(id);
			}
		}
	}

	cerr << "ans: " << ans << nl;
	if (ans > n) cout << "greater" << nl;
	else cout << 2*ans << nl;

	return 0;
}
