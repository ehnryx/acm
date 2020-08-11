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

	string s;
	cin >> s;
	int len = s.size();
	int half = s.size()/2;
	ll ans = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == s[(i+half)%len])
			ans += s[i]-'0';
	}
	cout << ans << nl;

	return 0;
}
