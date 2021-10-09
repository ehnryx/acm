#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-13;

const int D = 2;
typedef vector<ld> ndpt;
typedef list<ndpt>::iterator It;
struct Miniball { list<ndpt> L; int m; vector<vector<ld>> v, a; vector<ndpt> c;
  ndpt q0; vector<ld> r2, z, f; It end; ndpt c_c; ld c_r2;
  Miniball() : m(0), v(D+1,vector<ld>(D)), a(D+1,vector<ld>(D)), c(D+1, ndpt(D,0)),
      q0(D), r2(D+1), z(D+1), f(D+1), end(L.begin()), c_c(c[0]), c_r2(-1.L) {}
  void add(ndpt p) { L.push_back(p); }
  void move_to_front(It i) { m--; if (end == i) end++; L.splice(L.begin(), L, i); }
  void mtf_mb(It i) { end = L.begin(); if (m == D+1) return;
    for (It k = L.begin(), j; (j=k++) != i; ) { ld e = get_e(j); 
      if (e > 0 && push(*j)) mtf_mb(j), move_to_front(j); }}
  void pivot_mb(It i) {
    It t = ++L.begin(), pivot; mtf_mb(t); ld max_e, old_r2 = -1;
    do { if ((max_e = max_excess(t, i, pivot)) > 0) {
      if ((t=end)==pivot) ++t;
      old_r2 = c_r2; push(*pivot); mtf_mb(end); move_to_front(pivot); }
    } while (max_e > 0 && c_r2 > old_r2); }
  ld max_excess(It j, It i, It& pivot) { ld max_e = 0, e;
    for (; j!= i; ++j) if ((e=get_e(j)) > max_e) max_e=e, pivot=j; return max_e; }
  ld get_e(It j) { ld e=-c_r2; for (int i=0; i < D; i++) e += pow((*j)[i]-c_c[i], 2);
    return e; }
  bool push(const ndpt& p) { int i, j; if (!m) c[0]=q0=p, r2[0]=0; else {
    for (i = 0; i < D; i++) v[m][i] = p[i]-q0[i];
    for (i = 1; i < m; ++i) { a[m][i] = 0;
      for (j = 0; j < D; j++) a[m][i] += v[i][j]*v[m][j];
      a[m][i] *= (2/z[i]); }
    for (i = 1; i < m; i++) for (j = 0; j < D; j++) v[m][j] -= a[m][i]*v[i][j];
    z[m] = 0; for (j = 0; j < D; j++) z[m] += 2*pow(v[m][j], 2);
    if (z[m] < c_r2*EPS) return false;
    ld e = -r2[m-1]; for (i = 0; i < D; i++) e+= pow(p[i]-c[m-1][i], 2);
    f[m] = e/z[m];
    for (i = 0; i < D; i++) c[m][i] = c[m-1][i] + f[m]*v[m][i];
    r2[m] = r2[m-1] + e*f[m]/2;
  } c_c = c[m]; c_r2=r2[m]; m++; return true; }
  void build() { pivot_mb(L.end()); } } ;

#define sqr(X) (X)*(X)

ndpt to_ndpt(const pt& p) {
  return {real(p), imag(p)};
}

ostream& operator << (ostream& os, const pt& p) {
  os << "(" << real(p) << "," << imag(p) << ")"; return os;
}
bool by_angle(const pt& a, const pt& b) {
  return arg(a) < arg(b);
}

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }
inline bool cmp_lex(const pt& a, const pt& b) {
  return real(a) < real(b) - EPS || real(a) < real(b) + EPS && imag(a) < imag(b) - EPS;
}
bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1,b1-a1)*za), s2 = sgn(cp(a2-a1,b2-a1)*za);
  int s3 = sgn(cp(b2-b1,a1-b1)*zb), s4 = sgn(cp(b2-b1,a2-b1)*zb);
  if (!s1 && !s2 && !s3) {
    if (cmp_lex(a2,a1)) swap(a1,a2); if (cmp_lex(b2,b1)) swap(b1,b2);
    return !cmp_lex(b2,a1) && !cmp_lex(a2,b1);
  } return s1*s2 <= 0 && s3*s4 <= 0;
}

// ccw orientation
ld check_arc(pt a, pt b, pt old_center, ld radius2, const vector<pt>& bad, pt& new_center) {
  //cerr << "check arc " << a << " " << b << nl;
  ld x, y, z, s, K, tempr2;
  ld largest_r = 0;
  for (const pt& p : bad) {
    //cerr << "check bad: " << p << nl;
    if (sqr(abs(p - old_center)) < radius2 + EPS && seg_x_seg(a, b, old_center, p)) {
      pt pp = p + 10*EPS*(old_center-p);
      z = abs(a-b);
      x = abs(a-pp);
      y = abs(b-pp);
      s = (x+y+z)/2;
      K = s*(s-x)*(s-y)*(s-z);
      tempr2 = sqr(x*y*z) / (16*K);
      pt midp = 0.5L*(a+b);
      pt perp = perp = exp(pt(0,1))*(b-a);
      if (tempr2 > largest_r) {
        ld left = EPS;
        ld right = 1e7;
        ld mid;
        for (int i = 0; i < 1000 && right - left > EPS; i++) {
          mid = (left+right)/2;
          if (sqr(abs((midp + mid*perp) - (pp))) < tempr2)
            left = mid;
          else 
            right = mid;
        }
        new_center = midp + mid*perp;
        largest_r = tempr2;
      }
    }
  }
  //cerr << "returning largest_r: " << largest_r << nl;
  return largest_r;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);
  //cerr << fixed << setprecision(20);
  cout << fixed << setprecision(13);

  vector<pt> good, bad, hull;
  string s;
  while (getline(cin, s)) {
    // clear
    //cerr << nl;
    good.clear();
    bad.clear();
    hull.clear();
    // input
    istringstream in(s);
    string a; in >> a;
    char garbage;
    while (in >> garbage) {
      if (garbage == 'n')
        break;
      int x, y; in >> x >> garbage >> y >> garbage;
      good.push_back(pt(x, y));
    }
    getline(cin, s);
    istringstream iin(s);
    iin >> a;
    while (iin >> garbage) {
      if (garbage == 'n')
        break;
      int x, y; iin >> x >> garbage >> y >> garbage;
      bad.push_back(pt(x, y));
    }
    //cerr << "good: "; for (const pt& p : good)
      //cerr << p << " ";
    //cerr << nl;
    //cerr << "bad: "; for (const pt& p : bad)
      //cerr << p << " ";
    //cerr << nl;
    // code here
    // build miniball around good points
    Miniball good_mb;
    for (const pt& p : good) {
      //cerr << "add point " << p << nl;
      good_mb.add(to_ndpt(p));
    }
    good_mb.build();
    ld radius2 = good_mb.c_r2;
    pt center(good_mb.c_c[0], good_mb.c_c[1]);
    //cerr << "radius2: " << radius2 << nl;
    // find points on miniball
    for (const pt& p : good) {
      if (abs(sqr(abs(p - center)) - radius2) < EPS) {
        hull.push_back(p);
      }
    }
    sort(hull.begin(), hull.end(), by_angle);
    // check arcs
    pt new_center, temp_center;
    ld largest_r = 0;
    int n = hull.size();
    int bad_count = 0;
    for (int i = 0; i < n; i++) {
      ld temp_r = check_arc(hull[i], hull[(i+1)%n], center, radius2, bad, temp_center);
      if (temp_r > 0) {
        bad_count++;
        largest_r = max(largest_r, temp_r);
        new_center = temp_center;
      }
    }
    if (bad_count > 1) {
      // too many bad arcs
      cout << "The Orcs are close" << nl;
    } else if (bad_count == 0) {
      // no bad arcs
      cout << sqrt(radius2) << nl;
    } else {
      //cerr << nl << "one bad point found" << nl;
      //cerr << "largest_r: " << largest_r << " with center " << new_center << nl;
      for (const pt& p : bad) {
        if (sqr(abs(p - new_center)) < largest_r + EPS) {
          //cerr << "bad point at " << p << nl;
          bad_count++;
        }
      }
      if (bad_count == 1) {
        cout << sqrt(largest_r) << nl;
      } else {
        cout << "The Orcs are close" << nl;
      }
    }
  }

  return 0;
}
