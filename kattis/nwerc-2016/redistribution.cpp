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
	pii a[n];
	for (int i=0; i<n; i++) {
		cin >> a[i].first;
		a[i].second = i+1;
	}
	sort(a, a+n, greater<pii>());

	int sum = 0;
	for (int i=1; i<n; i++) {
		sum += a[i].first;
	}
	if (a[0].first > sum) {
		cout << "impossible" << nl;
	} else {
		for (int i=0; i<n; i++) {
			cout << a[i].second << " ";
		}
		cout << nl;
	}

	return 0;
}