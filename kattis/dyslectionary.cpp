#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void answer(vector<string>& cur) {
	sort(cur.begin(), cur.end());
	int len = 0;
	for (const string& s : cur) {
		len = max(len, (int)s.size());
	}
	for (string& s : cur) {
		while (s.size() < len) s.push_back(' ');
		reverse(s.begin(), s.end());
		cout << s << nl;
	}
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	string s;
	vector<string> cur;
	while (getline(cin, s)) {
		if (s.empty()) {
			answer(cur);
			cout << nl;
			cur.clear();
		} else {
			reverse(s.begin(), s.end());
			cur.push_back(s);
		}
	}
	if (!cur.empty()) {
		answer(cur);
	}

	return 0;
}
