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

const ld PI = acos((ld)-1);

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

int cc_inter(pt p1, ld r1, pt p2, ld r2, pt &i1, pt &i2) {
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2; pt c=(p1+p2)*0.5L + (p2-p1)*rq*0.5L/dq;
  ld dt=2.0*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if(dt < -EPS) return 0; if(dt < EPS) { i1=i2=c; return 1; }
  dt=sqrt(dt)*0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2;
}


//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(17);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	pt o(0,0);

	int T;
	cin >> T;
	while (T--) {

		int m, R;
		cin >> m >> R;

		ld ans = 2*PI*R;
		for (int i=0; i<m; i++) {
			int x, y, r;
			cin >> x >> y >> r;
			pt i1, i2, c(x,y);
			if (x*x+y*y==(R+r)*(R+r)) continue;
			if (r<R && x*x+y*y==(R-r)*(R-r)) {
				ans += 2*PI*r;
				continue;
			}
			if (cc_inter(o, R, c, r, i1, i2) == 2) {
				if (cp(c,i1)<0) swap(i1,i2);
				ld ang = arg(i1/i2);
				if (ang < -EPS) ang += 2*PI;
				ans -= ang*R;
				if (cp(i2-i1, c-i1) > 0) {
					ld cur = arg((i2-c)/(i1-c))*r;
					ans += cur;
				} else {
					ld cur = 2*PI*r - arg((i1-c)/(i2-c))*r;
					ans += cur;
				}
			}
		}
		cout << ans << nl;

	}

	return 0;
}
