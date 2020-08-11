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

	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;

	int vx1, vy1, vx2, vy2;
	cin >> vx1 >> vy1 >> vx2 >> vy2;

	function<ld(ld)> dist = [&] (ld t) {
		pt a = pt(x1,y1) + t*pt(vx1,vy1);
		pt b = pt(x2,y2) + t*pt(vx2,vy2);
		return abs(a-b);
	};

	ld left = 0;
	ld right = 1e17;
	for (int bs=0; bs<420; bs++) {
		ld lmid = (2*left+right)/3;
		ld rmid = (left+2*right)/3;
		if (dist(lmid) < dist(rmid)) {
			right = rmid;
		} else {
			left = lmid;
		}
	}
	cerr << "time: " << left << nl;
	cout << dist(left) << nl;

	return 0;
}
