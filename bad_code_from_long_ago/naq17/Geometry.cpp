// Everything Geometry

#include <iostream>
#include <cmath>

using namespace std;

// usually `#define ldouble double` is fine
// if more precision is needed, use long double instead
#define ldouble double

// epsilon, basically what will be used for 0
const ldouble EPS = 1e-12;

// the Point struct!
struct Point {
  ldouble x, y;
  Point() {}
  Point(ldouble x, ldouble y) : x(x), y(y) {}
  Point(const Point& p) : x(p.x), y(p.y) {}
  bool operator == (const Point& p) const {
    return abs(x-p.x) <= EPS && abs(y-p.y) <= EPS;
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

/**
 * dot is dot product
 * cross is cross product
 * dist2 is euclidean distance squared
 * dist is euclidean distance
 * area_tri is signed area of triangle a,b,c
 */
ldouble dot(const Point& a, const Point& b) {
  return a.x*b.x + a.y*b.y;
}
ldouble cross(const Point& a, const Point& b) {
  return a.x*b.y - a.y*b.x;
}
ldouble dist2(const Point& a, const Point& b) {
  return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
ldouble dist(const Point& a, const Point& b) {
  return sqrt(dist2(a,b));
}
ldouble area_tri(const Point& a, const Point& b, const Point& c) {
  return ((a.x*b.y + b.x*c.y + c.x*a.y) - (a.y*b.x + b.y*c.x + c.y*a.x))/2;
}

/**
 * returns true if segments a--b and x--y intersect
 * returns false otherwise
 */
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
  } else if (sgn1 > EPS || sgn2 > EPS) { // nonstrict (>=) to exclude endpoints
    return false;
  } else {
    return true;
  }
}

/**
 * test purposes
 */
int main() {
  Point a, b, c, d;
  // expects true (1)
  a = Point(0,0); b = Point(0,5); c = Point(-1, -1); d = Point(20, 21);
  cout << "segxseg " << a << " " << b << " " << c << " " << d << endl;
  cout << segxseg(a, b, c, d) << endl;
  return 0;
}
