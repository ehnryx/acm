#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-11;

// the Point struct!
struct Point {
  ldouble x, y;
  Point() {}
  Point(ldouble x, ldouble y) : x(x), y(y) {}
  Point(const Point& p) : x(p.x), y(p.y) {}
  bool operator == (const Point& p) const {
    return abs(x-p.x) <= EPS && abs(y-p.y) <= EPS;
  }
  bool operator != (const Point& other) {
    return !(*this == other);
  }
  Point operator + (const Point& p) const {
    return Point(x+p.x, y+p.y);
  }
  Point operator - (const Point& p) const {
    return Point(x-p.x, y-p.y);
  }
  Point operator * (double c) const {
    return Point(x*c, y*c);
  }
  Point operator / (double c) const {
    return Point(x/c, y/c);
  }
  Point rotate(double a) const {
    return Point(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a));
  }
};
ostream& operator << (ostream& os, const Point &p) {
  os << "(" << p.x << "," << p.y << ")";
  return os;
}

struct Line {
  ldouble a, b, c;
  Line(ldouble a, ldouble b, ldouble c) {
    this->a = a;
    this->b = b;
    this->c = c;
  }
};

ldouble dot(const Point& a, const Point& b) {
  return a.x*b.x + a.y*b.y;
}
ldouble dist(Point a, Point b) {
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
ldouble area_tri(const Point& a, const Point& b, const Point& c) {
  return ((a.x*b.y + b.x*c.y + c.x*a.y) - (a.y*b.x + b.y*c.x + c.y*a.x))/2;
}
bool segxseg(Point a, Point b, Point x, Point y) {
  // this line excludes the case where endpoints coincide
  if (a == x || a == y || b == x || b == y) return false;
  ldouble sgn1 = area_tri(a, b, x) * area_tri(a, b, y);
  ldouble sgn2 = area_tri(x, y, a) * area_tri(x, y, b);
  if (abs(sgn1) <= EPS && abs(sgn2) <= EPS) {
    if (dot(a-x, b-x) > EPS && dot(a-y, b-y) > EPS && dot(a-x, a-y) > EPS)
      return false;
    else
      return true;
  } else if (sgn1 >= EPS || sgn2 >= EPS) { // nonstrict (>=) to exclude endpoints
    return false;
  } else {
    return true;
  }
}
Point intersect(Line a, Line b, ldouble radius) {
  Point p, q, r, s;
  ldouble A, B, C, x, y;
  
  A = a.a*a.a + a.b*a.b;
  B = 2*a.b*a.c;
  C = a.c*a.c - radius*radius*a.a*a.a;
  y = (-B + sqrt(B*B - 4*A*C)) / (2*A);
  x = (a.b*y + a.c) / (-a.a);
  p = Point(x,y);
  y = (-B - sqrt(B*B - 4*A*C)) / (2*A);
  x = (a.b*y + a.c) / (-a.a);
  q = Point(x,y);

  A = b.a*b.a + b.b*b.b;
  B = 2*b.b*b.c;
  C = b.c*b.c - radius*radius*b.a*b.a;
  y = (-B + sqrt(B*B - 4*A*C)) / (2*A);
  x = (b.b*y + b.c) / (-b.a);
  r = Point(x,y);
  y = (-B - sqrt(B*B - 4*A*C)) / (2*A);
  x = (b.b*y + b.c) / (-b.a);
  s = Point(x,y);

  if (segxseg(p, q, r, s)) {
    y = (a.c*b.a - b.c*a.a) / (a.a*b.b - b.a*a.b);
    x = (a.b*y + a.c) / (-a.a);
    return Point(x,y);
  } else {
    return Point(1e7, 1e7);
  }
}
bool between(Point r, Point s, Line a, ldouble radius) {
  Point p, q;
  ldouble A, B, C, x, y;
  
  A = a.a*a.a + a.b*a.b;
  B = 2*a.b*a.c;
  C = a.c*a.c - radius*radius*a.a*a.a;
  y = (-B + sqrt(B*B - 4*A*C)) / (2*A);
  x = (a.b*y + a.c) / (-a.a);
  p = Point(x,y);
  y = (-B - sqrt(B*B - 4*A*C)) / (2*A);
  x = (a.b*y + a.c) / (-a.a);
  q = Point(x,y);

  //cerr << p << " " << q << endl;

  return segxseg(p,q,r,s);
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int a, b, c;
  int n, m, r;
  cin >> n >> m >> r;
  vector<Point> candle;
  vector<Point> pts;
  vector<Line> lines;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    candle.push_back(Point(a,b));
  }
  int cnt = 1;
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c;
    Line tl(a,b,c);
    // check
    pts.clear();
    cnt++; //cerr << "init" << nl;
    for (Line sad : lines) {
      Point tp = intersect(sad, tl, r);
      if (tp != Point(1e7, 1e7)) {
        for (Point it : pts) {
          if (dist(it, tp) <= EPS)
            goto next;
        }
        pts.push_back(tp);
        cnt++;
        //cerr << "++" << nl;
        next:;
      }
    }
    lines.push_back(tl);
  }
  //cerr << "pieces: " << cnt << nl;
  if (cnt != n) {
    cout << "no" << nl;
  } else {
    // check that there exists a line between each point
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        // check
        bool bad = true;
        for (Line li : lines) {
          if (between(candle[i], candle[j], li, r)) {
            bad = false;
            break;
          }
        }
        if (bad) {
          cout << "no" << nl;
          return 0;
        }
      }
    }
    cout << "yes" << nl;
  }

  return 0;
}
