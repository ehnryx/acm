#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
//typedef long double ld;
typedef double ld;
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

// Circumcenter of triangle defined by three points
// !!! used once on WF2018G
pt circumcenter(const pt& A, const pt& B, const pt& C) {
	ld a = norm(B-C), b = norm(C-A), c = norm(A-B);
	ld fa = a*(b+c-a), fb = b*(c+a-b), fc = c*(a+b-c);
	return (fa*A + fb*B + fc*C) / (fa+fb+fc);
}

/////////////////
// UBC code archive

struct p3d{ ld x,y,z; 
	p3d() {}
	p3d(ld x, ld y, ld z): x(x), y(y), z(z) {}
	friend ostream& operator<< (ostream& os, const p3d& p) {
		return os << "(" << p.x << "," << p.y << "," << p.z << ")"; 
	} 
};

ld abs(const p3d &v){ return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
p3d operator+(const p3d&a,const p3d&b){ return {a.x+b.x,a.y+b.y,a.z+b.z}; }
p3d operator-(const p3d&a,const p3d&b){ return {a.x-b.x,a.y-b.y,a.z-b.z}; }
p3d operator*(const ld &s, const p3d &v){ return {s*v.x, s*v.y, s*v.z}; }
p3d operator/(const p3d&v, const ld &s){ return {v.x/s, v.y/s, v.z/s}; }
inline ld dot(const p3d &a, const p3d &b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
inline p3d cross(const p3d &a, const p3d &b){
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; }
inline ld dist(const p3d &s, const p3d &p) {
  return (p.x-s.x)*(p.x-s.x) + (p.y-s.y)*(p.y-s.y) + (p.z-s.z)*(p.z-s.z); }
// plane/line intersection. p - pt on plane, n - normal, a1 -> a2 : line
inline p3d pl_inter(const p3d &p, const p3d &n, const p3d &a1, const p3d &a2){
  return a1 + dot(p - a1, n)/dot(n, a2 - a1)*(a2 - a1); 
}

namespace Hull {
	const int S = 11;
	const int MSK = (1<<S)-1;
	struct face{int a, b, c;}; int t, n; vector<pair<p3d,int>> v;
	ld dist(const face &f, const p3d p) {
	  return dot(cross(v[f.b].first-v[f.a].first, v[f.c].first-v[f.b].first), p-v[f.a].first); }
	ld area(const face &f){ return abs(cross(v[f.b].first - v[f.a].first, v[f.c].first - v[f.a].first)); }
	ld volume(const face &f){ p3d n=cross(v[f.b].first-v[f.a].first, v[f.c].first-v[f.b].first);
	  return area(f)*dot(n/abs(n), v[f.a].first)/6; }
	void convex_hull_clean_input() { shuffle(v.begin(), v.end(), rng);
	  for(int i=n-1; i>=0; i--) v[i].first = v[i].first - v[0].first;
	  for(int i=1; i<n; i++) if(abs(v[i].first-v[0].first) > EPS) { swap(v[i], v[1]); break; }
	  for(int i=2; i<n; i++) if(abs(cross(v[1].first-v[0].first, v[i].first-v[0].first)) > EPS) {
		swap(v[i], v[2]); break; }
	  for(int i=3; i<n; i++) { p3d n = cross(v[1].first - v[0].first, v[2].first - v[0].first);
		if(abs(dot(n, v[0].first - v[i].first)) > EPS) { swap(v[i], v[3]); break; } } 
	}

	vector<Tuple> solve(const vector<p3d>& p) { n = p.size();
	  for (int i = 0; i < n; i++) v.push_back(pair<p3d,int>(p[i], i));
	  convex_hull_clean_input();
	  vector<face> f { {0, 1, 2}, {2, 1, 0} };
	  for(int i=3; i<n; i++){ vector<face> nxt; set<int> edge;
		for(auto ff : f) // remove the faces
		  if(dist(ff, v[i].first) > EPS) { // above
			edge.insert((ff.a << S) | ff.b);
			edge.insert((ff.b << S) | ff.c);
			edge.insert((ff.c << S) | ff.a);
		  } else nxt.push_back(ff); // change shift and mask values for >1024 verts
		for(auto e : edge) if(!edge.count( ((e & MSK) << S) | (e >> S) ))
		  nxt.push_back(face{e >> S, e & MSK, i});
		f = nxt; }
	  // return faces
	  vector<Tuple> res;
	  for (auto ff : f) {
		  res.push_back(Tuple(v[ff.a].second, v[ff.b].second, v[ff.c].second));
	  }
	  return res;
	}
}

vector<Tuple> delaunay(const vector<pt>& p) {
	vector<p3d> points;
	for (const pt& it : p) {
		points.push_back(p3d(it.x, it.y, it.x*it.x+it.y*it.y));
	}
	return Hull::solve(points);
}

unordered_set<pt> voronoi(const vector<pt>& p) {
	int n = p.size();
	vector<Tuple> triangles = delaunay(p);
	//cerr << triangles.size() << " triangles" << endl;
	//cerr << "time: " << (ld)clock()/CLOCKS_PER_SEC << endl;

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
	//cerr << vx.size() << " points" << endl;
	//cerr << "time: " << (ld)clock()/CLOCKS_PER_SEC << endl;

	ld ans = 0;
	for (const pt& it : vx) {
		ld cur = INF;
		for (const pt& v : p) {
			cur = min(cur, abs(v-it));
		}
		ans = max(cur, ans);
	}
	cout << ans << nl;
	//cerr << "time: " << (ld)clock()/CLOCKS_PER_SEC << endl;

	return 0;
}
