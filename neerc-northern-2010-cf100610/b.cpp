#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

#define FILE "bug2"

const ld EPS = 1e-9;

struct Point {
  ld x, y;
  Point() {}
  Point(ld a, ld b) : x(a), y(b) {}
  Point operator+ (const Point& o) const {
    return Point(x+o.x, y+o.y);
  }
  Point operator- (const Point& o) const {
    return Point(x-o.x, y-o.y);
  }
  Point operator* (const ld& o) const {
    return Point(x*o, y*o);
  }
  Point operator/ (const ld& o) const {
    return Point(x/o, y/o);
  }
};

inline Point operator* (const ld& a, const Point& b) {
  return b*a;
}

inline ld dp(const Point& a, const Point& b) { return a.x*b.x + a.y+b.y; }
inline ld cp(const Point& a, const Point& b) { return a.x*b.y - a.y*b.x; }
inline ld abs(const Point& a) { return sqrt(a.x*a.x+a.y*a.y); }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }
inline bool cmp_lex(const Point& a, const Point& b) {
  return a.x<b.x-EPS||(a.x-b.x+EPS&&a.y<b.y-EPS);
}

inline Point line_inter(const Point& a, const Point& b, const Point& c, const Point& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

bool seg_x_seg(Point a1, Point a2, Point b1, Point b2) {
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0, zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
  int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
  if (!s1 && !s2 && !s3) {
    if (cmp_lex(a2, a1)) swap(a1, a2); if (cmp_lex(b2, b1)) swap(b1, b2);
    return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
  }
  return s1*s2 <= 0 && s3*s4 == 0;
}

struct Edge {
  Point a, b; // a->b
  int nxt;
  int isec_ind;
  bool seen;
  Edge() {}
  Edge(Point x, Point y) :a(x), b(y), isec_ind(0), nxt(0), seen(0) {}
};

struct Intersection {
  Point loc;
  int dir;
  int edge_ind;
  ld dist;
  bool is_f, is_s;
  bool operator< (const Intersection& o) const {
    return dist < o.dist;
  }
};


const int N = 300300;

Point s, f;
Point beg, fin;
Point poly[N];
Edge edges[N];
Intersection isec[N];
int n, ecount, icount;

int main() {
  if (fopen(FILE ".in", "r")) {
    freopen(FILE ".in", "r", stdin);
    freopen(FILE ".out", "w", stdout);
  }

  cin >> n >> s.x >> s.y >> f.x >> f.y;
  for (int i=1; i<=n; ++i) {
    int m;
    cin >> m;
    for (int j=1; j<=m; ++j) {
      cin >> poly[j].x >> poly[j].y;
    }
    for (int j=1; j<=m; ++j) {
      int k = j%m+1;
      edges[++ecount] = Edge(poly[j], poly[k]);
    }
  }

  assert(ecount == n);

  ld tlen = abs(f-s);
  ld factor = int(1e7/tlen);
  beg = f - factor*(f-s);
  fin = f + factor*(f-s);

  for(int i=1; i<=ecount; ++i) {
    if (seg_x_seg(edges[i].a, edges[i].b, beg, fin)) {
      ++icount;
      isec[icount].loc = line_inter(beg, fin, edges[i].a, edges[i].b);
      isec[icount].dist = abs(isec[icount].loc-beg);
      int sg = sgn(cp(f-s, edges[i].b-edges[i].a));
      isec[icount].dir = -sg;
    }
  }

  ++icount;
  isec[icount].loc = f;
  isec[icount].dist = abs(f-beg);
  isec[icount].is_f = 1;

  ++icount;
  isec[icount].loc = s;
  isec[icount].dist = abs(s-beg);
  isec[icount].is_s = 1;
  isec[icount].dir = 1;

  sort(isec+1, isec+icount+1);

  int find = 0, sind = 0;
  for (int i=1; i<=icount; ++i) {
    if (isec[i].is_f) {
      find = i;
    }
    if (isec[i].is_s) {
      sind = i;
    }
  }

  return 0;
}
