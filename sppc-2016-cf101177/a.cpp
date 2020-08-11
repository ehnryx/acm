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

int dist(const pii& a, const pii& b) {
	cerr << a.first << ',' << a.second << nl;
	cerr << b.first << ',' << b.second << nl;
	return abs(a.first-b.first) + abs(a.second-b.second);
}

pii find(int x) {
	if (x == 1) {
		return pii(0,0);
	}

	int lim = 1;
	while (lim*lim < x) { lim += 2; }

	int base = (lim-2)*(lim-2);
	for (int s = 0; s < 4; s++) {
		for (int i = 1; i < lim; i++) {
			if (x == base + s*(lim-1) + i) {
				if (s == 0) return pii(i - lim/2, 0 - lim/2);
				if (s == 1) return pii(lim/2, i - lim/2);
				if (s == 2) return pii(lim/2 - i, lim/2);
				if (s == 3) return pii(0 - lim/2, lim/2 - i);
			}
		}
	}
	assert(false);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int a, b;
	cin >> a >> b;
	cout << dist(find(a), find(b)) << nl;

	return 0;
}
