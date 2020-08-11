#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int ans = 0;
	int score = 0;
	string s;
	cin >> s;
	bool skip = false;
	bool garbage = false;
	int last = -1;
	for (int j = 0; j < s.size(); j++) {
		if (s[j] == '>') last = j;
	}
	int count = 0;
	for (int i = 0; i < s.size(); i++) {
		char c = s[i];
		if (skip) {
			skip = false;
			continue;
		}
		if (c == '!') {
			skip = true;
			continue;
		} else if (c == '>') {
			garbage = false;
		} else if (!garbage) {
			if (c == '<') {
				garbage = true;
			} else if (c == '{') {
				score++;
			} else if (c == '}') {
				ans += score;
				score--;
			}
		} else {
			count++;
		}
	}
	//cout << ans << nl;
	cout << count << nl;

	return 0;
}
