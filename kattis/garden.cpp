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

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld lp_dist(const pt& a, const pt& b, const pt& p) {
	return cp(b-a,p-a)/abs(b-a);
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

	int sz;
	cin >> sz;

	int a, b, x, y;
	cin >> a >> b;
	cin >> x >> y;
	pt s(a,b);
	pt t(x,y);
	pt o(0,0);

	auto valid = [&] (ld r) {
		ld d = abs(lp_dist(s,t,o));
		if (d>r) {
			return M_PIl*r*r >= sz;
		} else {
			ld ang = acos(d/r);
			ld area = (M_PIl-ang)*r*r + sin(ang)*r*d;
			return area >= sz;
		}
	};

	int left = 1;
	int right = INF;
	while (left<right) {
		int mid = (left+right)/2;
		if (valid(mid)) {
			right = mid;
		} else {
			left = mid+1;
		}
	}
	cout << left << nl;

	return 0;
}
