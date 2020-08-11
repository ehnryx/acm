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

int sqr(int x) { return x*x; }

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int r, x, y;
	cin >> r >> x >> y;

	int best = 1e5;
	bool good = false;
	for (int i=0; i<3; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (c < best) {
			best = c;
			if (sqr(x-a)+sqr(y-b)<r*r) {
				good = true;
			} else {
				good = false;
			}
		}
	}

	cout << (good ? "What a beauty!" : "Time to move my telescope!") << nl;

	return 0;
}
