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

	int n;
	cin >> n;

	int a;
	int m = 0;
	for (int i=0; i<n; i++) {
		cin >> a;
		m = max(m, a);
	}
	for (int i=0; i<n; i++) {
		cin >> a;
	}

	int k;
	cin >> k;

	int sum = 0;
	for (int i=0; i<k; i++) {
		cin >> a;
		sum += a;
	}

	cout << m*k+sum << nl;

	return 0;
}
