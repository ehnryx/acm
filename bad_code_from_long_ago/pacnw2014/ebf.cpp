#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;


bool hill_number(const char s[]) {
	int l = strlen(s);
	bool started_falling = false;
	for (int i = 1; i < l; i++) {
		if (!started_falling) {
			if (s[i] < s[i - 1]) {
				started_falling = true;
			}
		} else {
			if (s[i] > s[i - 1]) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int T; cin >> T;
	while (T--) {
		string s; cin >> s;
		if (!hill_number(s.c_str())) {
			cout << -1 << endl;
			continue;
		}
		int m = stoi(s);
		int ans = 0;
		for (int i = 0; i < m; i++)
			if (hill_number(to_string(i).c_str()))
				ans++;
		cout << ans << endl;
	}

	return 0;
}
