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
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
int sgn(const ld& x) { return x<-EPS ? -1 : x>EPS ? 1 : 0; }

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a,d-c) / cp(b-a,d-c) * (b-a);
}

ld area(const pol& v) { ld s = 0; int n = v.size();
  for (int i=n-1, j=0; j<n; i=j++) s += cp(v[i],v[j]);
  return abs(s)/2;
}

// Return number of intersections. Circles must not be identical.
int cc_inter(pt p1, ld r1, pt p2, ld r2, pt &i1, pt &i2) {
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2; pt c=(p1+p2)*0.5L + (p2-p1)*rq*0.5L/dq;
  ld dt=2.0*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if(dt < -EPS) return 0;
  if(dt < EPS) { i1=i2=c; return 1; }
  dt=sqrt(dt)*0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2;
}

// Left of the vector (a -> b) will be cut off. Convex polygons tested UVa 10117
// Simple polygon tested KTH Challenge 2013 G
pol cut_polygon(const pol &v, const pt &a, const pt &b) { pol out;
  for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    if(cp(b-a, v[i]-a) < EPS) out.push_back(v[i]);
    if(sgn(cp(b-a, v[i]-a)) * sgn(cp(b-a, v[j]-a)) < 0) {
      pt p = line_inter(a, b, v[i], v[j]);
      if(!out.size() || abs(out.back() - p) > EPS) out.push_back(p); } }
  while(out.size() && abs(out[0] - out.back()) < EPS) out.pop_back();
  return out;
}

// TODO we want to store after instead of before, then order of operations is reversed
struct Transform {
  pol before;
  ld sign;
  pt offset;
  Transform(const pol& before, ld s = 1, pt o = 0):
    before(before), sign(s), offset(o) {}
  Transform operator + (const pt& p) const {
    return Transform(before, sign, offset+p);
  }
  void translate(const pt& x) { offset += x; }
  bool empty() const { return before.empty(); }

  Transform cut(const pt& a, const pt& b) const {
    pol p = cut_polygon(before, a, b);
    return Transform(p, sign, offset);
  }

  vector<Transform> triangulate() const {
    vector<Transform> out;
    pol cur = before;
    for (int i = cur.size(); i > 3; i--) {
      out.push_back(Transform(cut_polygon(cur, cur[0], cur[2]), sign, offset));
      cur = cut_polygon(cur, cur[2], cur[0]);
    }
    out.push_back(Transform(cur, sign, offset));
    return out;
  }

  void output() const {
    assert(before.size() == 3);
    for (int i=2; i>=0; i--) {
      cout << before[i].real() << ' ' << before[i].imag() << ' ';
    }
    cout << nl;
    for (int i=2; i>=0; i--) {
      pt after = sign*before[i] + offset;
      cout << after.real() << ' ' << after.imag() << ' ';
    }
    cout << nl;
  }
};

Transform reflect(const pol& v, const pt& p) {
  return Transform(v, (ld)-1, (ld)2*p);
}

struct Triangle {
  pol original; // original
  vector<Transform> pieces;
  int rectLength;
  ld rectHeight;

  Triangle(int a, int b, int c) {
    if (b >= a && b >= c) {
      int t = b; b = c; c = a; a = t;
    } else if (c >= a && c >= b) {
      int t = c; c = b; b = a; a = t;
    }
    pt i1, i2;
    assert(cc_inter(pt(0,0), b, pt(a,0), c, i1, i2));
    if (i1.imag() < 0) swap(i1,i2);
    original.push_back(pt(0,0));
    original.push_back(pt(a,0));
    original.push_back(i1);
    rectLength = a;
    rectHeight = area(original)/a;
  }

  pol coordinates() {
    pol out = original;
    reverse(out.begin(), out.end());
    return out;
  }

  pol rectangle() {
    ld h = original.back().imag() / 2;
    pt leftp = line_inter(pt(0,h), pt(1,h), original[0], original.back());
    pt rightp = line_inter(pt(0,h), pt(1,h), original[1], original.back());
    pol top = cut_polygon(original, rightp, leftp);
    pol bottom = cut_polygon(original, leftp, rightp);
    pol left = cut_polygon(top, original.back(), original.back()-pt(0,1));
    pol right = cut_polygon(top, original.back(), original.back()+pt(0,1));
    pieces.push_back(Transform(bottom));
    pieces.push_back(reflect(left, leftp));
    pieces.push_back(reflect(right, rightp));
    return { pt(0,0), pt(0,h), pt(original[1].real(),h), original[1] };
  }

  void fit(int len, ld height) {
    vector<Transform> current = pieces;
    pieces.clear();
    int curlen = rectLength;
    pt offset = 0;
    while (curlen != len) {
      if (curlen < len) {
        pt left = pt(0, height);
        pt right = pt(len, height);
        for (Transform& it : current) {
          Transform done = it.cut(left, right);
          if (!done.empty()) pieces.push_back(done + offset);
          it.before = cut_polygon(it.before, right, left);
        }
      } else {
      }
    }
  }

  // ONLY CALL ONCE at the END
  void output() {
    vector<Transform> out;
    for (const Transform& it : pieces) {
      for (const Transform& cut : it.triangulate()) {
        out.push_back(cut);
      }
    }

    cout << out.size() << nl;
    assert(out.size() <= 1000);
    for (const Transform& it : out) {
      it.output();
    }
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int x, y, z;
  cin >> x >> y >> z;
  Triangle T1(x,y,z);
  cin >> x >> y >> z;
  Triangle T2(x,y,z);

  // Output original triangles
  for (const pt& it : T1.coordinates()) {
    cout << it.real() << ' ' << it.imag() << ' ';
  }
  cout << nl;
  for (const pt& it : T2.coordinates()) {
    cout << it.real() << ' ' << it.imag() << ' ';
  }
  cout << nl;

  // Fit first triangle into a rectangle
  for (const pt& it : T1.rectangle()) {
    cout << it.real() << ' ' << it.imag() << ' ';
  }
  cout << nl;

  // Fit second triangle into the rectangle
  T2.rectangle();
  T2.fit(T1.rectLength, T1.rectHeight);

  // Output answer
  T1.output();
  T2.output();

  return 0;
}
