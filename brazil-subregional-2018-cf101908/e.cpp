#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	string s, t; cin >> s >> t;
	int ans = 0;
	for (int i = 0; i+t.size() <= s.size(); i++) {
		bool shit = 0;
		for (int j = 0; j < t.size(); j++) {
			if (t[j] == s[i+j]) {
				shit = 1;
				break;
			}
		}
		ans += !shit;
	}
	cout << ans << nl;

	return 0;
}
