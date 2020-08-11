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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;

		int bed, kitchen, living;
		bed = kitchen = living = 0;

		string s;
		for (int i=0; i<n; i++) {
			cin >> s;
			if (s.substr(0,3) == "bed") {
				bed++;
			} else if (s.substr(0,6) == "living") {
				living++;
			} else {
				kitchen++;
			}
		}

		cout << min(bed/2, min(living, kitchen)) << nl;
	}

	return 0;
}
