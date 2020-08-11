#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	string s, t;
	cin >> s >> t;

	if (s.size() != t.size()) {
		cout << "NO" << nl;
		return 0;
	} else {
		int n = s.size();
		int first = 0;
		int last = n-1;
		while (first < n && s[first] == t[first]) {
			first++;
		}
		while (last >= 0 && s[last] == t[last]) {
			last--;
		}
		if (first > last) {
			cout << "YES" << nl;
			return 0;
		} else {
			for (int i = 0; i < last-first+1; i++) {
				if (s[first+i] != t[last-i]) {
					cout << "NO" << nl;
					return 0;
				}
			}
			cout << "YES" << nl;
			return 0;
		}
	}

	return 0;
}
