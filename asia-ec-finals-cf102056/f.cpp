#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-10;

struct p3d {
	ld x,y,z;
	p3d(ld x, ld y, ld z): x(x), y(y), z(z) {}
};

p3d operator + (const p3d& a, const p3d& b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
p3d operator - (const p3d& a, const p3d& b) { return {a.x-b.x, a.y-b.y, a.z-b.z}; }
p3d operator * (const p3d& v, const ld& s) { return {v.x*s, v.y*s, v.z*s}; }
p3d operator / (const p3d& v, const ld& s) { return {v.x/s, v.y/s, v.z/s}; }
ld abs(const p3d& v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
ld dot(const p3d& a, const p3d& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {

		ld x, y, z, r;
		cin >> x >> y >> z >> r;
		p3d o(x,y,z);
		cin >> x >> y >> z;
		p3d s(x,y,z);
		cin >> x >> y >> z;
		p3d t(x,y,z);

		p3d u = (t-s)/abs(t-s);
		p3d m = s + u*dot(u,o-s);

		if (abs(m-o) < r && abs(abs(s-m)+abs(m-t)-abs(s-t)) < EPS) {
			ld ss = abs(s-o);
			ld tt = abs(t-o);
			ld totang = acos(dot(s-o,t-o)/ss/tt);
			ld stangent = sqrt(ss*ss - r*r);
			ld ttangent = sqrt(tt*tt - r*r);
			ld ang = totang - acos(r/ss) - acos(r/tt);
			cout << stangent + ttangent + r*ang << nl;
		} else {
			cout << abs(s-t) << nl;
		}

	}

	return 0;
}
