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
		string s;
		cin >> s;
		reverse(s.begin(), s.end());
		int ans = 0;
		for (int i=0; i<s.size(); i++) {
			int a = stoi(s.substr(i,1));
			if (i%2==1) {
				if (2*a<10) ans += 2*a;
				else ans += 2*a-9;
			} else {
				ans += a;
			}
		}
		cout << (ans%10==0 ? "PASS" : "FAIL") << nl;
	}

	return 0;
}
