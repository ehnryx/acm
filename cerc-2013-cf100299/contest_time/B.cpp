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

	int T; cin >> T;
	string s; getline(cin, s);
	while (T--) {
		getline(cin, s);
		istringstream in(s);
		vector<string> v;
		while (in >> s) v.push_back(s);
		vector<bool> use(v.size(), 1);
		while (getline(cin, s)) {
			istringstream in(s);
			in >> s >> s;
			if (s[0] == 'd') {
				for (int i = 0; i < v.size(); i++) {
					if (use[i]) {
						cout << v[i] << " ";
					}
				}
				cout << nl;
				break;
			} else {
				in >> s;
				for (int i = 0; i < v.size(); i++) {
					if (v[i] == s) {
						use[i] = 0;
					}
				}
			}
		}
	}

	return 0;
}
