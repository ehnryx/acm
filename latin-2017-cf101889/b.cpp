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

bool isvowel(char c) {
	return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';
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
	cin >> s;

	vector<int> cnt;
	cnt.push_back(0);
	for (char c : s) {
		if (isvowel(c)) {
			cnt.push_back(0);
		} else {
			cnt.back()++;
		}
	}

	if (cnt.size() == 1) {
		cout << 1 << nl;
	}
	else if (cnt[0] > 0) {
		cout << 0 << nl;
	}
	else {
		cout << 1+cnt[cnt.size()/2] << nl;
	}

	return 0;
}
