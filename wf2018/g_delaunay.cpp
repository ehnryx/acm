#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
//typedef double ld;
typedef pair<int,int> pii;
//typedef complex<ld> pt;
//typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template<class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	os << "[ ";
	for (const T& it : v) os << it << ' ';
	return os << ']';
}
template<class T>
ostream& operator << (ostream& os, const unordered_set<T>& v) {
	os << "{ ";
	for (const T& it : v) os << it << ' ';
	return os << '}';
}

template<class T> struct cplx {
  T x, y; cplx() {x = 0.0; y = 0.0;}
  cplx(T nx, T ny=0) {x = nx; y = ny;}
  cplx operator+(const cplx &c) const {return {x + c.x, y + c.y};}
  cplx operator-(const cplx &c) const {return {x - c.x, y - c.y};}
  cplx operator*(const cplx &c) const {return {x*c.x - y*c.y, x*c.y + y*c.x};}
  cplx& operator*=(const cplx &c) { return *this={x*c.x-y*c.y, x*c.y+y*c.x}; }
  // Only supports right scalar multiplication like p*c
  template<class U> cplx operator*(const U &c) const {return {x*c,y*c};}
  template<class U> cplx operator/(const U &c) const {return {x/c,y/c};} };
#define polar(r,a)  (pt){r*cos(a),r*sin(a)}
typedef cplx<ld> pt;
typedef vector<pt> pol;
pt operator*(ld c, const pt p) { return {p.x*c,p.y*c};} // for left mult. c*p
// useful for debugging
ostream&operator<<(ostream &o,const pt &p){o<<"("<<p.x<<","<<p.y<<")";return o;}
ld cp(const pt& a, const pt& b) { return a.x*b.y - b.x*a.y; }
ld dp(const pt& a, const pt& b) { return a.x*b.x + a.y*b.y; }
inline ld abs(const pt &a) {return sqrt(a.x*a.x + a.y*a.y);}
inline ld arg(const pt &a) {return atan2(a.y,a.x);}
ld ang(pt &a, pt &b, pt &c) { return atan2(cp(a-b,b-c),dp(a-b,b-c)); }
inline bool cmp_lex(const pt& a, const pt& b) {
  return a.x<b.x-EPS||(a.x<b.x+EPS&&a.y<b.y-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.y<b.y-EPS||(a.y<b.y+EPS&&a.x<b.x-EPS);
}

ld norm(const pt& x) { return x.x*x.x + x.y*x.y; }
// dist(const pt& a, const pt& b) ==> abs(a-b)
inline bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
inline int sgn(const ld& x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }
// handles ALL cases, uncomment/edit the 3 marked lines to exclude endpoints
bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
  //if (eq(a1,a2) || eq(b1,b2)) return false; // uncomment to exclude endpoints
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
  int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
  if(!s1 && !s2 && !s3) { // collinear, in our purposes it is bad
    return false;
  } return s1*s2 <= 0 && s3*s4 <= 0; } //change to < to exclude endpoints

inline pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }

// Closest pt on line segment (a, b) to pt p.
inline pt lsp_closest(const pt &a, const pt &b, const pt &p) {
  if (dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0)
    return abs(cp(b-a, p-a)) < EPS ? p : line_inter(a, b, p, p+(a-b)*pt(0,1));
  return abs(a - p) < abs(b - p) ? a : b; }

// Does NOT include points on the ends of the segment.
inline bool on_segment(const pt &a, const pt &b, const pt &p) {
  return abs(cp(b-a, p-a)) < EPS && dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0; }

// Checks if p lies on the boundary of a polygon v.
inline bool on_boundary(const pol &v, const pt &p) { bool res = false;
  for(int i=v.size()-1,j=0;j<v.size();i=j++)
    res |= on_segment(v[i], v[j], p) | (abs(p-v[i]) < EPS); return res; }

// orientation does not matter !!!
bool pt_in_polygon(const pt &p, const pol &v){ if(on_boundary(v,p)) return true;
  ld res = 0; for(int i = v.size() - 1, j = 0; j < v.size(); i = j++)
    res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p));
  return abs(res) > 1; 
} // will be either 2*PI or 0

pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch; 
} // pts returned in ccw order.

/////////////////
// LCA

int inc(int i, int m) { return i+1==m?0:i+1; }

// Circumcenter of triangle defined by three points
// !!! used once on WF2018G
pt circumcenter(const pt& A, const pt& B, const pt& C) {
	ld a = norm(B-C), b = norm(C-A), c = norm(A-B);
	ld fa = a*(b+c-a), fb = b*(c+a-b), fc = c*(a+b-c);
	return (fa*A + fb*B + fc*C) / (fa+fb+fc);
}

////////////////////////////////////////////////////////////////////////
// Delaunay Triangulation -- used once on WF2018G 
// returns the delaunay triangulation as triples of indices

struct Tuple { vi v;
	Tuple() {}
	Tuple(int a, int b) { v={a,b}; sort(v.begin(), v.end()); }
	Tuple(int a, int b, int c) { v={a,b,c}; sort(v.begin(),v.end()); }
	bool operator == (const Tuple& t) const { return v == t.v; }
	int operator [] (int i) const { return v[i]; }
};
namespace std {
	template<> struct hash<Tuple> {
		size_t operator () (const Tuple& t) const {
			size_t h = 0;
			for (int i = 0; i < t.v.size(); i++)
				h ^= hash<int>()(t[i]<<(10*i));
			return h;
		}
	};
	bool operator == (const pt& a, const pt& b) { return eq(a,b); }
	template<> struct hash<pt> {
		size_t operator () (const pt& t) const {
			return hash<ld>()(1e5*t.x) ^ hash<ld>()(t.y);
		}
	};
}

vector<Tuple> delaunay(vector<pt> p) {
	int n = p.size();

	p.push_back(pt(INF,INF));
	p.push_back(pt(INF,-INF));
	p.push_back(pt(-INF,0));

	unordered_set<Tuple> cur;
	cur.insert(Tuple(n, n+1, n+2));

	unordered_map<Tuple,int> cnt;
	for (int i = 0; i < n; i++) {
		vector<Tuple> add; // edge
		vector<Tuple> bad; // triangle

		cnt.clear();
		for (const Tuple& tri : cur) {
			pt cc = circumcenter(p[tri[0]], p[tri[1]], p[tri[2]]);
			if (abs(p[i]-cc) < abs(p[tri[0]]-cc)) {
				bad.push_back(tri);
				for (int j = 0; j < 3; j++) {
					cnt[Tuple(tri[j], tri[inc(j,3)])]++;
				}
			}
		}

		for (const Tuple& tri : bad) {
			for (int j = 0; j < 3; j++) {
				cur.erase(tri);
				if (cnt[Tuple(tri[j], tri[inc(j,3)])] == 1) {
					add.push_back(Tuple(tri[j], tri[inc(j,3)]));
				}
			}
		}

		for (const Tuple& e : add) {
			cur.insert(Tuple(i, e[0], e[1]));
		}
	}

	vector<Tuple> res;
	for (const Tuple& tri : cur) {
		if (tri[0] < n && tri[1] < n && tri[2] < n) res.push_back(tri);
	}

	return res;
}

unordered_set<pt> voronoi(const vector<pt>& p) {
	int n = p.size();
	vector<Tuple> triangles = delaunay(p);
	cerr << triangles.size() << " triangles" << endl;

	unordered_set<pt> circ;
	for (const Tuple& tri : triangles) {
		pt cc = circumcenter(p[tri[0]], p[tri[1]], p[tri[2]]);
		if (pt_in_polygon(cc, p)) {
			circ.insert(cc);
		}
		for (int i = 0; i < 3; i++) {
			pt end = (ld)0.5*(p[tri[i]]+p[tri[i+1==3?0:i+1]]);
			for (int j = 0; j < n; j++) {
				if (seg_x_seg(end, cc, p[j], p[j+1==n?0:j+1])) {
					circ.insert(line_inter(end, cc, p[j], p[j+1==n?0:j+1]));
				}
			}
		}
	}

	return circ;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	int a, b;
	vector<pt> p;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		p.push_back(pt(a,b));
	}
	unordered_set<pt> vx = voronoi(p);
	cerr << vx.size() << " points" << endl;

	ld ans = 0;
	for (const pt& it : vx) {
		ld cur = INF;
		for (const pt& v : p) {
			cur = min(cur, abs(v-it));
		}
		ans = max(cur, ans);
	}
	cout << ans << nl;

	return 0;
}
