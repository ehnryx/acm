#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Frac {
	ll n, d;
	Frac(const ll& a=0, const ll& b=1) {
		ll g = abs(__gcd(a,b));
		n = a/g; d = b/g;
		if(d==0) { n = abs(n); }
		if(d<0) { n = -n; d = -d; }
	}
	bool operator < (const Frac& o) const { return n*o.d < d*o.n; }
	bool operator == (const Frac& o) const { return n*o.d == d*o.n; }
	Frac operator + (const Frac& o) const { return Frac(n*o.d+d*o.n, d*o.d); }
	Frac operator - (const Frac& o) const { return Frac(n*o.d-d*o.n, d*o.d); }
	Frac operator * (const Frac& o) const { return Frac(n*o.n, d*o.d); }
	Frac operator / (const Frac& o) const { return Frac(n*o.d, d*o.n); }
};

struct Point {
	Frac x, y;
	Point(const Frac& _x=0, const Frac& _y=0): x(_x), y(_y) {}
	bool operator < (const Point& o) const { return x<o.x || (x==o.x && y<o.y); }
	bool operator == (const Point& o) const { return x==o.x && y==o.y; }
	Frac operator * (const Point& o) const { return x*o.y - y*o.x; }
	Point operator + (const Point& o) const { return Point(x+o.x, y+o.y); }
	Point operator - (const Point& o) const { return Point(x-o.x, y-o.y); }
	Point operator * (const Frac& o) const { return Point(x*o, y*o); }
};

struct Segment {
	Point a, b;
	Segment(const Point& u, const Point& v): a(min(u,v)), b(max(u,v)) {}
	Point dir() const { return b - a; }
};

bool parallel(const Segment& u, const Segment& v) {
	return u.dir() * v.dir() == Frac(0);
}

bool same_line(const Segment& u, const Segment& v) {
	return u.dir() * (v.a-u.a) == Frac(0);
}

int sgn(const Frac& x) {
	return x<Frac(0) ? -1 : (Frac(0)<x ? 1 : 0);
}

bool seg_x_seg(const Segment& u, const Segment& v) {
	int s1 = sgn(u.dir()*(v.a-u.a)); int s2 = sgn(u.dir()*(v.b-u.a));
	int s3 = sgn(v.dir()*(u.a-v.a)); int s4 = sgn(v.dir()*(u.b-v.a));
	return s1*s2 <= 0 && s3*s4 <= 0;
}

Point intersect(const Segment& u, const Segment& v) {
	return u.a + u.dir() * ((v.a-u.a)*v.dir() / (u.dir()*v.dir()));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	vector<Segment> segs;
	set<Point> pts;
	for(int i=0;i<n;i++) {
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		segs.push_back(Segment(Point(a,b),Point(c,d)));
		for(int j=0;j<i;j++) {
			if(parallel(segs[i], segs[j])) {
				if(same_line(segs[i], segs[j])) {
					if(segs[i].a < segs[j].b && segs[j].a < segs[i].b) {
						cout<<-1<<nl;
						return 0;
					} else if(segs[i].a == segs[j].b) {
						pts.insert(segs[i].a);
					} else if(segs[i].b == segs[j].a) {
						pts.insert(segs[i].b);
					}
				}
			} else if(seg_x_seg(segs[i], segs[j])) {
				pts.insert(intersect(segs[i], segs[j]));
			}
		}
	}
	cout<<pts.size()<<nl;

	return 0;
}
