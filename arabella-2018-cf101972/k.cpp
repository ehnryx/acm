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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		string s, t;
		cin >> s;
		cin >> t;

		vector<char> a, b;
		for (int i=0; i<n; i++) {
			if (s[i] != t[i]) {
				a.push_back(s[i]);
				b.push_back(t[i]);
			}
		}

		n = a.size();
		bool ok = true;
		for (int i=n-1,j=0; j<n; i=j++) {
			ok &= (a[j] == b[i]);
		}
		cout << (ok ? "YES" : "NO") << nl;
	}

	return 0;
}
