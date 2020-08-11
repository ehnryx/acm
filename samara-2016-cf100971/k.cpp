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

	string s;
	cin >> s;
	int n = s.size();

	if (n%2 == 0) {
		{
			int m = n/2;
			int ans = -1;
			for (int i=0; i<n/2; i++) {
				if (s[m+i] != s[m-i-(ans!=-1)]) {
					if (ans != -1) {
						ans = -2;
						break;
					} else if (s[m+i] != s[m-i-1]) {
						ans = -2;
						break;
					} else {
						ans = m-i;
					}
				}
			}
			if (ans != -2) {
				cout << "YES" << nl;
				if (ans == -1) {
					cout << 1 << nl;
				} else {
					cout << ans+1 << nl;
				}
				return 0;
			}
		}
		{
			int m = n/2-1;
			int ans = -1;
			for (int i=0; i<n/2; i++) {
				if (s[m+i+(ans!=-1)] != s[m-i]) {
					if (ans != -1) {
						ans = -2;
						break;
					} else if (s[m+i+1] != s[m-i]) {
						ans = -2;
						break;
					} else {
						ans = m+i;
					}
				}
			}
			if (ans != -2) {
				cout << "YES" << nl;
				if (ans == -1) {
					cout << n << nl;
				} else {
					cout << ans+1 << nl;
				}
				return 0;
			}
		}
	} else {
		{
			int m = n/2;
			int ans = m;
			for (int i=1; i<=n/2; i++) {
				if (s[m-i] != s[m+i]) {
					ans = -1;
					break;
				}
			}
			if (ans != -1) {
				cout << "YES" << nl;
				cout << ans+1 << nl;
				return 0;
			}
		}
		{
			int m = n/2;
			int ans = -1;
			for (int i=0; i<n/2; i++) {
				if (s[m+i+1] != s[m-i-(ans!=-1)]) {
					if (ans != -1) {
						ans = -2;
						break;
					} else if (s[m+i+1] != s[m-i-1]) {
						ans = -2;
						break;
					} else {
						ans = m-i;
					}
				}
			}
			if (ans != -2) {
				cout << "YES" << nl;
				if (ans == -1) {
					cout << 1 << nl;
				} else {
					cout << ans+1 << nl;
				}
				return 0;
			}
		}
		{
			int m = n/2;
			int ans = -1;
			for (int i=0; i<n/2; i++) {
				if (s[m+i+(ans!=-1)] != s[m-i-1]) {
					if (ans != -1) {
						ans = -2;
						break;
					} else if (s[m+i+1] != s[m-i-1]) {
						ans = -2;
						break;
					} else {
						ans = m+i;
					}
				}
			}
			if (ans != -2) {
				cout << "YES" << nl;
				if (ans == -1) {
					cout << n << nl;
				} else {
					cout << ans+1 << nl;
				}
				return 0;
			}
		}
	}

	cout << "NO" << nl;

	return 0;
}
