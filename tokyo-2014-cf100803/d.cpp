#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';
const ld EPS = 1e-10;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << fixed << setprecision(10);

	int d, n, b;
	cin >> d >> n >> b;

	int p[n], h[n];
	for (int i=0; i<n; i++) {
		cin >> p[i] >> h[i];
	}

	ld ans = 1e42;
	for (int i=0; i<=b; i++) {
		ld jmp = (ld)d/(i+1);
		ld ubx = 1e42;
		for (int j=0; j<n; j++) {
			ld x = p[j];
			while (x > jmp) { x -= jmp; }
			ubx = min(ubx, sqrt((jmp*x-x*x)/(2*h[j])));
		}

		auto calc = [&] (ld v) {
			return v*v+(jmp/v)*(jmp/v)/4;
		};

		ld left, right;
		left = 0;
		right = ubx;
		while (right-left > EPS) {
			ld first = (2*left+right)/3;
			ld second = (left+2*right)/3;
			if (calc(first) < calc(second)) {
				right = second;
			} else {
				left = first;
			}
		}

		for (ld j=0.1; j<ubx; j+=0.1) {
			cerr << j << ": " << calc(j) << nl;
		}
		cerr << "SOLVE " << i << " : " << calc(left+right)/2 << nl;

		ans = min(ans, calc((left+right)/2));
	}
	cout << sqrt(ans) << nl;

	return 0;
}
