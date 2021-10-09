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

struct Point {
  ld x, y;
  char t;
  Point(){}
  Point(const ld& x, const ld& y, char t = 0): x(x), y(y), t(t) {}
  bool operator < (const Point& v) const {
    if (x == v.x) return y < v.y;
    else return x < v.x;
  }
  friend ostream& operator << (ostream& os, const Point& v) {
    return os << '(' << v.x << ',' << v.y << ')';
  }
};

ld sqr(const ld& x) { return x*x; }

ld dist2(const Point& a, const Point& b) {
  return sqr(a.x-b.x) + sqr(a.y-b.y);
}

pair<Point,ld> circle(const Point& A, const Point& B) {
  Point center = Point((A.x+B.x)/2, (A.y+B.y)/2);
  return pair<Point,ld>(center, dist2(center, A));
}

pair<Point,ld> circumcircle(const Point& A, const Point& B, const Point& C) {
  ld a2 = dist2(B, C);
  ld b2 = dist2(C, A);
  ld c2 = dist2(A, B);
  ld fa = a2*(b2+c2-a2);
  ld fb = b2*(c2+a2-b2);
  ld fc = c2*(a2+b2-c2);

  if (abs(fa+fb+fc) > EPS) {
    Point center = Point((fa*A.x + fb*B.x + fc*C.x) / (fa+fb+fc), (fa*A.y + fb*B.y + fc*C.y) / (fa+fb+fc));
    return pair<Point,ld>(center, dist2(center, A));
  } else {
    return circle(A,B);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  int a, b;
  char t;
  vector<Point> p;
  for (int i=0; i<n; i++) {
    cin >> a >> b >> t;
    p.push_back(Point(a,b,t));
  }
  shuffle(p.begin(), p.end(), rng);

  for (int i=0; i<n; i++) {
    for (int j=0; j<i; j++) {
      for (int k=0; k<j; k++) {
        bool good = true;
        Point center;
        ld radius2;
        tie(center, radius2) = circumcircle(p[i], p[j], p[k]);
        for (const Point& it : p) {
          ld d2 = dist2(center, it);
          if (it.t == 'I' && d2 > radius2+EPS) {
            good = false;
            break;
          }
          if (it.t == 'N' && d2 < radius2-EPS) {
            good = false;
            break;
          }
        }
        if (good) {
          cout << "No" << nl;
          return 0;
        }
      }

      bool good = true;
      Point center;
      ld radius2;
      tie(center, radius2) = circle(p[i], p[j]);
      for (const Point& it : p) {
        ld d2 = dist2(center, it);
        if (it.t == 'I' && d2 > radius2+EPS) {
          good = false;
          break;
        }
        if (it.t == 'N' && d2 < radius2-EPS) {
          good = false;
          break;
        }
      }
      if (good) {
        cout << "No" << nl;
        return 0;
      }
    }
  }

  if (n < 3) {
    cout << "No" << nl;
  } else {
    cout << "Yes" << nl;
  }

  return 0;
}
