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

void solve(int n, int k, char s, char t, char o) {
	if (n == 1) {
		if (k % 2 == 1) {
			cout << s << " " << t << nl;
			k -= 1;
		} else {
			cout << s << " " << o << nl;
			cout << o << " " << t << nl;
			k -= 2;
		}
		while (k > 0) {
			cout << t << " " << o << nl;
			cout << o << " " << t << nl;
			k -= 2;
		}
	}
	else {
		solve(n-1, k, s, o, t);
		cout << s << " " << t << nl;
		solve(n-1, 1, o, t, s);
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

	int n, k;
	cin >> n >> k;
	if (k < (1<<n)-1) {
		cout << "N" << nl;
	} else {
		cout << "Y" << nl;
		solve(n, k - ((1<<n)-1) + 1, 'A', 'C', 'B');
	}

	return 0;
}
