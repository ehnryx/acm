#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef double ld;
//typedef complex<ld> pt;

const ld PI = acos((ld)-1);
const ld EPS = 1e-10;
const ld E = 1e-8;
//const int MAGIC = 4;
const int MAGIC = 7e3;

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
typedef cplx<ld> pt;
pt operator*(ld c, const pt p) { return {p.x*c,p.y*c};} // for left mult. c*p
#define polar(r,a)  (pt){r*cos(a),r*sin(a)}
// useful for debugging
ostream&operator<<(ostream &o,const pt &p){o<<"("<<p.x<<","<<p.y<<")";return o;}
ld cp(const pt& a, const pt& b) { return a.x*b.y - b.x*a.y; }
ld dp(const pt& a, const pt& b) { return a.x*b.x + a.y*b.y; }
inline ld abs(const pt &a) {return sqrt(a.x*a.x + a.y*a.y);}
inline bool cmp_lex(const pt& a, const pt& b) {
  return a.x<b.x-EPS||(a.x<b.x+EPS&&a.y<b.y-EPS);
}

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}

//ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
int sgn(const ld& x) { return x<-EPS?-1:x>EPS?1:0; }

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a,d-c)/cp(b-a,d-c) * (b-a);
}

bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
  //if (eq(a1,a2) || eq(b1,b2)) return false; // uncomment to exclude endpoints
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
  int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
  if(!s1 && !s2 && !s3) { // collinear
    if (cmp_lex(a2, a1)) swap(a1, a2); if (cmp_lex(b2, b1)) swap(b1, b2);
    //return cmp_lex(a1, b2) && cmp_lex(b1, a2);//uncomment to exclude endpoints
    return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
  } return s1*s2 <= 0 && s3*s4 <= 0;
} //change to < to exclude endpoints

struct Rectangle {
	pt w, x, y, z;
	vector<pt> v;
	Rectangle(int x1, int y1, int x2, int y2):
		w(x1-E,y1-E), x(x1-E,y2+E), y(x2+E,y2+E), z(x2+E,y1-E), v({w,x,y,z}) {}
	vector<pt> intersect(const pt& a, const pt& b) const {
		vector<pt> out;
		if (seg_x_seg(a,b,w,x)) out.push_back(line_inter(a,b,w,x));
		if (seg_x_seg(a,b,x,y)) out.push_back(line_inter(a,b,x,y));
		if (seg_x_seg(a,b,y,z)) out.push_back(line_inter(a,b,y,z));
		if (seg_x_seg(a,b,z,w)) out.push_back(line_inter(a,b,z,w));
		return out;
	}
};
vector<Rectangle> rect;

int solve(const pt& s, const pt& t, int len) {
	vector<pair<ld,int>> line;
	pt dir = (t-s)/abs(t-s);
	pt left = s-(ld)1e5*dir;
	pt right = s+(ld)1e5*dir;
	for (const Rectangle& r : rect) {
		vector<pt> cur = r.intersect(left,right);
		if (!cur.empty()) {
			pt lb = right;
			pt ub = left;
			for (const pt& it : cur) {
				if (abs(left-it) < abs(left-lb)) lb = it;
				if (abs(left-it) > abs(left-ub)) ub = it;
			}
			line.push_back(pair<ld,int>(abs(left-lb),-1));
			line.push_back(pair<ld,int>(abs(left-ub),1));
		}
	}
	line.push_back(pair<ld,int>(-1e42,1));
	sort(line.begin(), line.end());

	int res = 0;
	int n = line.size();
	int j = 0;
	for (int i=0; i<n; i++) {
		if (line[i].second == -1) {
			while (j<i && line[i].first-line[j].first > len) {
				j++;
			}
			res = max(res, (i-j+1)/2);
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, len;
	cin >> n >> len;

	int x1, y1, x2, y2;
	vector<pt> p;
	for (int i=0; i<n; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		rect.push_back(Rectangle(x1,y1,x2,y2));
		p.push_back(pt(x1,y1));
		p.push_back(pt(x1,y2));
		p.push_back(pt(x2,y2));
		p.push_back(pt(x2,y1));
	}

	vector<pt> ang;
	for (int j=0; j<MAGIC; j++) {
		ang.push_back(polar(1,PI*j/MAGIC));
	}

	n = p.size();
	int ans = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<i; j++) {
			ans = max(ans, solve(p[i],p[j],len));
		}
	}
	for (int i=0; i<n; i++) {
		for (const pt& it : ang) {
			ans = max(ans, solve(p[i],p[i]+it,len));
		}
	}
	cout << ans+1 << nl;

	return 0;
}
