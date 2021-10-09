#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(chrono::high_resolution_clock::now().time_since_epoch().count()); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-13;

////////////////////////////////////////////////////////////////////////////////
// General 2D geometry, Polygon cutting, Point in polygon
////////////////////////////////////////////////////////////////////////////////
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }

// dist(const pt& a, const pt& b) ==> abs(a-b)
inline bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }

inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}

// handles ALL cases, uncomment/edit the 3 marked lines to exclude endpoints
bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
  //if (eq(a1,a2) || eq(b1,b2)) return false; // uncomment to exclude endpoints
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
  int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
  if(!s1 && !s2 && !s3) { // collinear
    if (cmp_lex(a2, a1)) swap(a1, a2); if (cmp_lex(b2, b1)) swap(b1, b2);
    //return cmp_lex(a1, b2) && cmp_lex(b1, a2);//uncomment to exclude endpoints
    return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
  } return s1*s2 <= 0 && s3*s4 <= 0; } //change to < to exclude endpoints

inline pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }

// Projection of (a -> p) to vector (a -> b), SIGNED - positive in front
inline ld proj_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) / abs(b - a); }

// SIGNED distance. Pt on the right of vector (a -> b) will be NEGATIVE.
inline ld lp_dist(const pt &a, const pt &b, const pt &p) {
  return cp(b - a, p - a) / abs(b - a); }

// Line segment (a, b) to pt p distance.
inline ld lsp_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0 ?
    abs(cp(b - a, p - a) / abs(b - a)) : min(abs(a - p), abs(b - p)); }

// Closest pt on line segment (a, b) to pt p.
inline pt lsp_closest(const pt &a, const pt &b, const pt &p) {
  if (dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0)
    return abs(cp(b-a, p-a)) < EPS ? p : line_inter(a, b, p, p+(a-b)*pt(0,1));
  return abs(a - p) < abs(b - p) ? a : b; }

// Area of a polygon (convex or concave). Always non-negative.
ld area(const pol &v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]); return s/2; }

// orientation does not matter
pt centroid(const pol &v) {
  pt res; ld A = 0; int n = v.size();
  for(int i=n-1,j=0;j<n;i=j++) A+=cp(v[i],v[j]), res+=(v[i]+v[j])*cp(v[i],v[j]);
  return abs(A) < EPS ? res : res/3.L/A; }

// Left of the vector (a -> b) will be cut off. Convex polygons tested UVa 10117
// Simple polygon tested KTH Challenge 2013 G
pol cut_polygon(const pol &v, const pt &a, const pt &b) { pol out;
  for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    if(cp(b-a, v[i]-a) < EPS) out.push_back(v[i]);
    if(sgn(cp(b-a, v[i]-a)) * sgn(cp(b-a, v[j]-a)) < 0) {
      pt p = line_inter(a, b, v[i], v[j]);
      if(!out.size() || abs(out.back() - p) > EPS) out.push_back(p); } }
  while(out.size() && abs(out[0] - out.back()) < EPS) out.pop_back();
  return out; }

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
  return abs(res) > 1; } // will be either 2*PI or 0
////////////////////////////////////////////////////////////////////////////////

struct cmp_pt {
  bool operator () (const pt& a, const pt& b) const {
    return cmp_lex(a,b);
  }
};

pt base;
pt near(const pt& a, const pt& b) {
  return (abs(a-base) < abs(b-base)) ? a : b;
}

map<pt, set<pt, cmp_pt>, cmp_pt> nextpt, prevpt;
vector<pt> points, reflect;

pt find_next(const pt& cur, const pt& prev) {
  if (nextpt[cur].size() == 1) {
    return *nextpt[cur].begin();
  }
  else {
    ////cerr << "FIND at " << cur << " from " << prev << endl;
    pt left = *nextpt[cur].begin();
    pt right = *nextpt[cur].rbegin();
    ld sl = sgn(cp(cur - prev, left - prev));
    ld sr = sgn(cp(cur - prev, right - prev));
    ////cerr << "\tleft: " << left << "  right: " << right << "  sl: " << sl << "  sr: " << sr << endl;
    if (sl == 0 && sr == 0) {
      ////cerr << "\ttwo zeroes, compare dp " << endl;
      return dp(left - cur, cur - prev) < dp(right - cur, cur - prev) ? left : right;
    } else if (sr != sl) {
      ////cerr << "\tnot equal, sl > sr ? left : right " << endl;
      return (sl > sr) ? left : right;
    } else {
      ////cerr << "\tequal signs, compare left->right angle, > 0 ? right : left " << endl;
      return sgn(cp(left - cur, right - cur)) > 0 ? right : left;
    }
  }
}

void get_next(int n, const pt& start, const pt& end) {
  if (eq(start, end)) return;
  base = start;
  pt nxt = end;
  for (int i = 0; i < n; i++) {
    if (abs(cp(start - end, points[i] -points[(i+1)%n])) > EPS
        && seg_x_seg(start, end, points[i], points[(i+1)%n])) {
      pt inter = line_inter(start, end, points[i], points[(i+1)%n]);
      if (!eq(base, inter))
        nxt = near(nxt, inter);
    }
  }
  for (int i = 0; i < n; i++) {
    if (abs(cp(start - end, reflect[i] - reflect[(i+1)%n])) > EPS
        && seg_x_seg(start, end, reflect[i], reflect[(i+1)%n])) {
      pt inter = line_inter(start, end, reflect[i], reflect[(i+1)%n]);
      if (!eq(base, inter))
        nxt = near(nxt, inter);
    }
  }
  nextpt[start].insert(nxt);
  prevpt[nxt].insert(start);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  srand();

  int n;
  cin >> n;

  int a, b, x, y;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    points.push_back(pt(a,b));
  }
  if (area(points) < 0) {
    reverse(points.begin(), points.end());
  }

  cin >> a >> b >> x >> y;
  pt first(a,b);
  pt second(x,y);

  for (int i = 0; i < n; i++) {
    pt inter = proj_dist(first, second, points[i]) / abs(second - first) * (second - first) + first;
    reflect.push_back(inter + inter - points[i]);
  }
  reverse(reflect.begin(), reflect.end());

  //cerr << "original:  " << points << endl;
  //cerr << "reflected: " << reflect << endl;
  //cerr << endl;

  for (int i = 0; i < n; i++) {
    get_next(n, points[i], points[(i+1)%n]);
    get_next(n, reflect[i], reflect[(i+1)%n]);
    for (int j = 0; j < n; j++) {
      if (abs(cp(points[i]-points[(i+1)%n], reflect[j]-reflect[(j+1)%n])) > EPS
          && seg_x_seg(points[i], points[(i+1)%n], reflect[j], reflect[(j+1)%n])) {
        pt inter = line_inter(points[i], points[(i+1)%n], reflect[j], reflect[(j+1)%n]);
        get_next(n, inter, points[(i+1)%n]);
        get_next(n, inter, reflect[(j+1)%n]);
      }
    }
  }

  ld ans = 0;
  set<pt, cmp_pt> vis;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (abs(cp(points[i]-points[(i+1)%n], reflect[j]-reflect[(j+1)%n])) > EPS
          && seg_x_seg(points[i], points[(i+1)%n], reflect[j], reflect[(j+1)%n])) {
        pt cur = line_inter(points[i], points[(i+1)%n], reflect[j], reflect[(j+1)%n]);
        pt nxt = find_next(cur, *prevpt[cur].begin());
        pt other = find_next(cur, *prevpt[cur].rbegin());
        if (!eq(nxt, other))
          continue;

        if (!vis.count(cur)) {
          vector<pt> polygon;
          pt prev = *prevpt[cur].begin();
          while (!vis.count(cur)) {
            vis.insert(cur);
            polygon.push_back(cur);
            nxt = find_next(cur, prev);
            prev = cur;
            cur = nxt;
          }

          //cerr << nl;
          //cerr << "POLY: " << polygon << " <-- " << area(polygon) << nl << endl;
          ans += abs(area(polygon));

          for (const pt& it : polygon) {
            nxt = find_next(it, *prevpt[it].begin());
            other = find_next(it, *prevpt[it].rbegin());
            if (!eq(nxt, other)) {
              vis.erase(it);
              //cerr << "-----erase " << it << endl;
            }
          }
        }
      }
    }
  }

  //cerr << endl << "ANSWER: " << endl;
  cout << ans/2 << nl;

  return 0;
}
