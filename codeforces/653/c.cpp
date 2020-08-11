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

	int n;
	cin >> n;

	int a[n];
	vector<bool> up(n);
	vector<bool> down(n);
	down[0] = true;
	for (int i=0; i<n; i++) {
		cin >> a[i];
		if (i && a[i]>=a[i-1]) up[i] = true;
		if (i && a[i]<=a[i-1]) down[i] = true;
	}

	vector<int> s;
	for (int i=1; i<n; i++) {
		if (up[i] == up[i-1] || down[i] == down[i-1]) {
			s.push_back(i);
		}
	}

	auto valid = [&] () {
		int p = INF;
		for (int i=0; i<n; i++) {
			if (i%2 == 0 && a[i] >= p) return false;
			if (i%2 == 1 && a[i] <= p) return false;
			p = a[i];
		}
		return true;
	};

	cerr << s.size() << nl;
	if (s.size() > 17) {
		cout << 0 << nl;
	} else {
		int ans = 0;
		for (int i : s) {
			for (int j : s) {
				swap(a[i], a[j]);
				ans += valid();
				swap(a[i], a[j]);
			}
		}
		cout << ans << nl;
	}

	return 0;
}
