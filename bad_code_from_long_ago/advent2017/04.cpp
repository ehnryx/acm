#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int ans = 0;
	string s;
	while (getline(cin, s)) {
		istringstream ss(s);
		set<string> a;
		bool good = true;
		while (ss >> s) {
			sort(s.begin(), s.end());
			if (a.count(s))
				good = false;
			a.insert(s);
		}
		if (good) ans++;
	}
	cout << ans << nl;

	return 0;
}
