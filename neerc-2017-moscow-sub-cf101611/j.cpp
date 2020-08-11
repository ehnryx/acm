#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
//typedef complex<ld> pt;
//typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
const ld BS = 1e-8;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

template<class T> struct cplx {
  T x, y; cplx() {x = 0.0; y = 0.0;}
  cplx(T nx, T ny=0) {x = nx; y = ny;}
  cplx operator+(const cplx &c) const {return {x + c.x, y + c.y};}
  cplx operator-(const cplx &c) const {return {x - c.x, y - c.y};}
  cplx operator*(const cplx &c) const {return {x*c.x - y*c.y, x*c.y + y*c.x};}
  cplx& operator*=(const cplx &c) { return *this={x*c.x-y*c.y, x*c.y+y*c.x}; }
  // Only supports right scalar multiplication like p*c
  template<class U> cplx operator*(const U &c) const {return {x*c,y*c};}
  template<class U> cplx operator/(const U &c) const {return {x/c,y/c};}
};
#define polar(r,a)  (pt){r*cos(a),r*sin(a)}
typedef cplx<ld> pt;
typedef vector<pt> pol;
pt operator*(ld c, const pt p) { return {p.x*c,p.y*c};} // for left mult. c*p
ld cp(const pt& a, const pt& b) { return a.x*b.y - b.x*a.y; }
ld dp(const pt& a, const pt& b) { return a.x*b.x + a.y*b.y; }
inline ld abs(const pt &a) {return sqrt(a.x*a.x + a.y*a.y);}
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }

inline pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a);
}

// Area of a polygon (convex or concave). Always non-negative.
ld area(const pol &v) {
	ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]);
	return s/2;
}

// Left of the vector (a -> b) will be cut off. Convex polygons tested UVa 10117
// Simple polygon tested KTH Challenge 2013 G
inline pol cut_polygon(const pol &v, const pt &a, const pt &b) {
	pol out;
  for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    if(cp(b-a, v[i]-a) < EPS) out.push_back(v[i]);
    if(sgn(cp(b-a, v[i]-a)) * sgn(cp(b-a, v[j]-a)) < 0) {
      pt p = line_inter(a, b, v[i], v[j]);
      if(!out.size() || abs(out.back() - p) > EPS) out.push_back(p); } }
  while(out.size() && abs(out[0] - out.back()) < EPS) out.pop_back();
  return out;
}

vector<vector<pt>> p;
ld calc(const ld& w, const ld& h, const ld& lx, const ld& rx, const ld& ly, const ld& ry) {
	pt a(lx,ly), b(lx,ry), c(rx,ry), d(rx,ly);
	ld tot = (min(w,rx)-lx) * (min(h,ry)-ly);
	for (const vector<pt>& tri : p) {
		vector<pt> cur = cut_polygon(tri, a, b);
		cur = cut_polygon(cur, b, c);
		cur = cut_polygon(cur, c, d);
		cur = cut_polygon(cur, d, a);
		tot -= area(cur);
	}
	return tot;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(9);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, w, h;
	//cin >> n >> w >> h;
	read(n); read(w); read(h);

	ld miss = w*h;
	for (int i=0; i<n; i++) {
		vector<pt> tri;
		for (int j=0; j<3; j++) {
			int x, y;
			//cin >> x >> y;
			read(x); read(y);
			tri.emplace_back(x,y);
		}
		if (area(tri) < 0) {
			reverse(tri.begin(), tri.end());
		}
		p.push_back(tri);
		miss -= area(tri);
	}

	ld lx, rx, ly, ry;
	lx = ly = 0;
	rx = ry = max(w,h);
	while (rx-lx > BS && clock() < 1.789*CLOCKS_PER_SEC) {
		ld mx = (lx+rx)/2;
		ld my = (ly+ry)/2;
		ld left = calc(w, h, lx, mx, ly, ry);
		if (left > miss/2) {
			ld down = calc(w, h, lx, mx, ly, my);
			if (down > left/2) {
				rx = mx;
				ry = my;
				miss = down;
			} else {
				rx = mx;
				ly = my;
				miss = left-down;
			}
		} else {
			ld right = miss-left;
			ld down = calc(w, h, mx, rx, ly, my);
			if (down > right/2) {
				lx = mx;
				ry = my;
				miss = down;
			} else {
				lx = mx;
				ly = my;
				miss = right-down;
			}
		}
	}

	cout << (lx+rx)/2 << ' ' << (ly+ry)/2 << nl;

	return 0;
}
