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

	int s, g;
	cin >> s >> g;
	if (s % g == 0) {
		for(int i = 1; i < s/g && clock() < 1.9*CLOCKS_PER_SEC; i++) {
			if (__gcd(i, s/g-i) == 1) {
				cout << i*g << " " << s-i*g << nl;
				return 0;
			}
		}
		cout << -1 << nl;
	}
	else {
		cout << -1 << nl;
	}

	return 0;
}
