#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#define USE_RATIONAL_POINTS

// START #include "../../lca/number/fraction.h"

#ifdef USE_INT128
__int128 gcd(const __int128& a, const __int128& b) {
  if(b == 0) return a < 0 ? -a : a;
  return gcd(b, a % b);
}
string to_string(const __int128& v) {
  bool neg = v < 0;
  string out;
  for(__int128 n=neg?-v:v; n; n/=10) {
    out.push_back(n % 10 + '0');
  }
  if(out.empty()) out.push_back('0');
  if(neg) out.push_back('-');
  reverse(begin(out), end(out));
  return out;
}
ostream& operator << (ostream& os, const __int128& v) {
  return os << to_string(v);
}
#endif

template <typename T, bool overflow_guard = false>
struct fraction {
  T num, den;
  explicit fraction(const T& n = 0, const T& d = 1) {
    T g = gcd(n, d);
    num = d < 0 ? -n/g : n/g;
    den = d < 0 ? -d/g : d/g;
  }
  fraction(const pair<T, T>& f): num(f.first), den(f.second) {} // skip gcd
  template <typename F> fraction(const fraction<F>& o): num(o.num), den(o.den) {}
  const T& numerator() const { return num; }
  const T& denominator() const { return den; }
  T floor() const { return num < 0 ? (num - den + 1) / den : num / den; }
  friend ostream& operator << (ostream& os, const fraction& v) {
    return os << v.numerator() << '/' << v.denominator();
  }
  fraction operator - () const { return fraction(pair(-num, den)); }
  fraction operator + (const fraction& o) const { return fraction(*this) += o; } 
  fraction operator - (const fraction& o) const { return fraction(*this) -= o; }
  fraction operator * (const fraction& o) const { return fraction(*this) *= o; }
  fraction operator / (const fraction& o) const { return fraction(*this) /= o; }
  fraction& operator += (const fraction& o) {
    T g = gcd(den, o.den);
    den /= g;
    num = num * (o.den / g) + o.num * den;
    g = gcd(num, g);
    num /= g;
    den *= o.den / g;
    return *this;
  }
  fraction& operator -= (const fraction& o) {
    T g = gcd(den, o.den);
    den /= g;
    num = num * (o.den / g) - o.num * den;
    g = gcd(num, g);
    num /= g;
    den *= o.den / g;
    return *this;
  }
  fraction& operator *= (const fraction& o) {
    T gn = gcd(num, o.den);
    T gd = gcd(den, o.num);
    num = num / gn * o.num / gd;
    den = den / gd * o.den / gn;
    return *this;
  }
  fraction& operator /= (const fraction& o) {
    T gn = gcd(num, o.num);
    T gd = gcd(den, o.den);
    num = num / gn * (o.num < 0 ? -o.den : o.den) / gd;
    den = den / gd * (o.num < 0 ? -o.num : o.num) / gn;
    return *this;
  }
  bool operator < (const fraction& o) const {
    if (den == 0 && o.den == 0) return num && o.num && num < o.num;
    if (den == 0) return num < 0;
    if (o.den == 0) return 0 < o.num;
    if constexpr (overflow_guard) {
      T y = floor();
      T oy = o.floor();
      if (y != oy) return y < oy;
      return compare_fractions(num - den * y, den, o.num - o.den * oy, o.den);
    } else {
      return num * o.den < o.num * den;
    }
  }
  bool compare_fractions(const T& a, const T& b, const T& c, const T& d) const {
    if (b == d || a == 0 || c == 0) return a < c;
    return 2*a > b && 2*c > d ? fraction(d-c, d) < fraction(b-a, b) :
      fraction(d, c) < fraction(b, a);
  }
  bool operator > (const fraction& o) const { return o < *this; }
  bool operator == (const fraction& o) const { return num == o.num && den == o.den; }
  bool operator <= (const fraction& o) const { return operator == (o) || operator < (o); }
  bool operator >= (const fraction& o) const { return o <= *this; }
  template <typename D> D value() const { return D(num) / D(den); }
  explicit operator double() const { return value<double>(); }
  explicit operator long double() const { return value<long double>(); }
  fraction abs() const { return fraction(pair(num < 0 ? -num : num, den)); }
  template <typename D = long double> D sqrt() const { return std::sqrt(value<D>()); }
};

template <typename T, bool G> auto abs(const fraction<T,G>& v) { return v.abs(); }
template <typename T, bool G> auto sqrt(const fraction<T,G>& v) { return v.sqrt(); }

// END #include "../../lca/number/fraction.h"
// START #include "../../lca/geometry2d/point.h"

template <typename T = long double>
struct point {
  T x, y;
  point() = default;
  point(const T& c): x(c), y(0) {}
  point(const T& _x, const T& _y): x(_x), y(_y) {}
  friend ostream& operator << (ostream& os, const point& v) {
    return os << '(' << v.x << ',' << v.y << ')';
  }
  bool operator < (const point& v) const { return tie(x, y) < tie(v.x, v.y); }
  bool operator == (const point& v) const { return x == v.x && y == v.y; }
  point operator + (const point& v) const { return point(x + v.x, y + v.y); }
  point operator - (const point& v) const { return point(x - v.x, y - v.y); }
  point operator * (const point& v) const { return point(x*v.x - y*v.y, x*v.y + y*v.x); }
  point operator / (const point& v) const { return (*this) * v.inverse(); }
  point operator * (const T& c) const { return point(x*c, y*c); }
  point operator / (const T& c) const { return point(x/c, y/c); }
  friend point operator * (const T& c, const point& v) { return v*c; }
  point inverse() const { return conj() / norm(); }
  point conj() const { return point(x, -y); }
  point perp() const { return point(-y, x); }
  T real() const { return x; }
  T imag() const { return y; }
  template <typename D = T>
  T norm() const { return x*x + y*y; }
  T dot(const point& v) const { return x*v.x + y*v.y; }
  T cross(const point& v) const { return x*v.y - y*v.x; }
#ifndef USE_RATIONAL_POINTS
  T arg() const { return atan2(y, x); }
  T abs() const { return sqrt(norm()); }
  static point polar(const T& r, const T& angle) {
    return point<T>(r * cos(angle), r * sin(angle));
  }
  static bool by_angle(const point& a, const point& b) {
    return a.arg() < b.arg();
  }
#endif
};

template <typename T> auto real(const point<T>& v) { return v.real(); }
template <typename T> auto imag(const point<T>& v) { return v.imag(); }
template <typename T> auto conj(const point<T>& v) { return v.conj(); }
template <typename T> auto perp(const point<T>& v) { return v.perp(); }
template <typename T> auto norm(const point<T>& v) { return v.norm(); }
template <typename T> auto dot(const point<T>& a, const point<T>& b) { return a.dot(b); }
template <typename T> auto cross(const point<T>& a, const point<T>& b) { return a.cross(b); }

#ifndef USE_RATIONAL_POINTS
template <typename T> auto arg(const point<T>& v) { return v.arg(); }
template <typename T> auto abs(const point<T>& v) { return v.abs(); }

template <typename T>
bool equal(const point<T>& a, const point<T>& b, const T& eps = 1e-9) {
  return abs(a - b) <= eps;
}

template <typename T>
int sign(const T& x, const T& eps = 1e-9) {
  return x < -eps ? -1 : x > eps ? 1 : 0;
}

#else
template <typename T>
bool equal(const point<T>& a, const point<T>& b) { return a == b; }

template <typename T>
int sign(const T& x) { return x < T(0) ? -1 : T(0) < x ? 1 : 0; }

template <typename T>
int sign_cross(const point<T>& a, const point<T>& b) {
  T left = a.x * b.y;
  T right = a.y * b.x;
  return left == right ? 0 : left < right ? -1 : 1;
}

template <typename T>
int sign_dot(const point<T>& a, const point<T>& b) {
  T left = a.x * b.x;
  T right = -a.y * b.y;
  return left == right ? 0 : left < right ? -1 : 1;
}
#endif

// END #include "../../lca/geometry2d/point.h"
// START #include "../../lca/geometry2d/general.h"

// START #include "point.h"
// already included
// END #include "point.h"

#ifndef USE_RATIONAL_POINTS
template <typename T>
bool collinear(
    const point<T>& a, const point<T>& b, const point<T>& c,
    const T& eps = 1e-9) {
  return abs(a-c) <= eps || abs(cross(a-c, b-c) / abs(a-c)) <= eps;
}

template <typename T>
bool parallel(
    const point<T>& a, const point<T>& b, const point<T>& c, const point<T>& d,
    const T& eps = 1e-9) {
  return abs(cross(a-b, c-d)) / abs(a-b) <= eps;
}

#else
template <typename T>
bool collinear(const point<T>& a, const point<T>& b, const point<T>& c) {
  return a == c || sign_cross(a-c, b-c) == 0;
}

template <typename T>
bool parallel(const point<T>& a, const point<T>& b, const point<T>& c, const point<T>& d) {
  return sign_cross(a-b, c-d) == 0;
}
#endif

template <typename T>
point<T> line_inter(
    const point<T>& a, const point<T>& b,
    const point<T>& c, const point<T>& d) {
  return a + cross(c-a, d-c) / cross(b-a, d-c) * (b-a);
}

#ifndef USE_RATIONAL_POINTS
template <typename T>
bool on_segment(
    const point<T>& a, const point<T>& b, const point<T>& c,
    bool strict = false, const T& eps = 1e-9) {
  if (equal(a, c, eps) || equal(b, c, eps)) return !strict;
  return collinear(a, b, c, eps) && dot(a - b, c - b) > 0 && dot(b - a, c - a) > 0;
}

template <typename T>
bool on_boundary(const vector<point<T>>& v, const point<T>& c, const T& eps = 1e-9) {
  bool ok = false;
  for (int i = (int)size(v) - 1, j = 0; !ok && j < size(v); i = j++) {
    ok |= on_segment(v[i], v[j], c, false, eps);
  }
  return ok;
}

template <typename T>
bool in_polygon(
    const vector<point<T>>& v, const point<T>& c,
    bool strict = false, const T& eps = 1e-9) {
  if (on_boundary(v, c, eps)) return !strict;
  T sum = 0;
  for (int i = (int)size(v) - 1, j = 0; j < size(v); i = j++) {
    sum += atan2(cross(v[i] - c, v[j] - c), dot(v[i] - c, v[j] - c));
  }
  return abs(sum) > 1;
}

template <typename T>
bool seg_x_seg(
    const point<T>& a, const point<T>& b,
    const point<T>& c, const point<T>& d,
    bool strict = false, const T& eps = 1e-9) {
  T ab = abs(a - b);
  if (ab <= eps) return on_segment(c, d, a, strict, eps);
  T cd = abs(c - d);
  if (cd <= eps) return on_segment(a, b, d, strict, eps);
  int r1 = sign(cross(a - b, a - c) / ab, eps);
  int r2 = sign(cross(a - b, a - d) / ab, eps);
  if (r1 == 0 && r2 == 0) {
    return strict ? min(a, b) < max(c, d) && min(c, d) < max(a, b) :
        !(max(a, b) < min(c, d) || max(c, d) < min(a, b));
  }
  int r3 = sign(cross(c - d, c - a) / cd, eps);
  int r4 = sign(cross(c - d, c - b) / cd, eps);
  return strict ? r1*r2 < 0 && r3*r4 < 0 : r1*r2 <= 0 && r3*r4 <= 0;
}

#else
template <typename T>
bool on_segment(
    const point<T>& a, const point<T>& b, const point<T>& c,
    bool strict = false) {
  if (a == c || b == c) return !strict;
  return collinear(a, b, c) && sign_dot(a - b, c - b) > 0 && sign_dot(b - a, c - a) > 0;
}

template <typename T>
bool on_boundary(const vector<point<T>>& v, const point<T>& c, const T& eps = 1e-9) {
  bool ok = false;
  for (int i = (int)size(v) - 1, j = 0; !ok && j < size(v); i = j++) {
    ok |= on_segment(v[i], v[j], c, false);
  }
  return ok;
}

template <typename D = long double, typename T>
bool in_polygon(const vector<point<T>>& v, const point<T>& c, bool strict = false) {
  if (on_boundary(v, c)) return !strict;
  D sum = 0;
  for (int i = (int)size(v) - 1, j = 0; j < size(v); i = j++) {
    sum += atan2(D(cross(v[i] - c, v[j] - c)), D(dot(v[i] - c, v[j] - c)));
  }
  return abs(sum) > 1;
}

template <typename T>
bool seg_x_seg(
    const point<T>& a, const point<T>& b,
    const point<T>& c, const point<T>& d,
    bool strict = false) {
  if (a == b) return on_segment(c, d, a, strict);
  if (c == d) return on_segment(a, b, d, strict);
  int r1 = sign_cross(a - b, a - c);
  int r2 = sign_cross(a - b, a - d);
  if (r1 == 0 && r2 == 0) {
    return strict ? min(a, b) < max(c, d) && min(c, d) < max(a, b) :
        !(max(a, b) < min(c, d) || max(c, d) < min(a, b));
  }
  int r3 = sign_cross(c - d, c - a);
  int r4 = sign_cross(c - d, c - b);
  return strict ? r1*r2 < 0 && r3*r4 < 0 : r1*r2 <= 0 && r3*r4 <= 0;
}
#endif

// END #include "../../lca/geometry2d/general.h"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-13L;
random_device _rd; mt19937 rng(_rd());

using F = fraction<ll>;
using P = point<F>;

const int N = 12;
bool exists[N][N][N];
bool intersect[N][N][N][N][N][N];

bool valid(const vector<int>& v, int i, int j, int k) {
  if(!exists[i][j][k]) return false;
  for(int s=2; s<size(v); s++) {
    if(v[s-1] == i || v[s-1] == j || v[s-1] == k) continue;
    if(intersect[i][j][k][v[s-1]][v[s]][v[s-2]]) return false;
  }
  return true;
}

int solve(int bm, vector<int>& order) {
  int n = size(order);
  if(bm == 0) {
    return valid(order, order[n-1], order[n-2], order[0])
      && valid(order, order[0], order[1], order[n-1]);
  }
  int res = 0;
  for(int i=0; i<N; i++) {
    if(!(bm & 1<<i)) continue;
    if(n < 2 || valid(order, order[n-1], order[n-2], i)) {
      order.push_back(i);
      res += solve(bm ^ 1<<i, order);
      order.pop_back();
    }
  }
  return res;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<pair<P,P>> lines;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    lines.emplace_back(P(F(a), F(b)), P(F(x), F(y)));
  }

  vector rank(n, vector<int>(n, -1));
  vector<tuple<int,int,int>> segs;
  for(int i=0; i<n; i++) {
    map<P,vector<int>> order;
    for(int j=0; j<n; j++) {
      if(parallel(lines[i].first, lines[i].second, lines[j].first, lines[j].second)) continue;
      P ij = line_inter(lines[i].first, lines[i].second, lines[j].first, lines[j].second);
      order[ij].push_back(j);
    }
    int rid = 0;
    for(const auto& [it, ids] : order) {
      for(int j : ids) {
        rank[i][j] = rid;
      }
      rid++;
    }
    for(int j=0; j<n; j++) {
      if(rank[i][j] == -1) continue;
      for(int k=0; k<n; k++) {
        if(rank[i][k] == -1) continue;
        exists[i][j][k] = (rank[i][j] != rank[i][k]);
        segs.emplace_back(i, j, k);
      }
    }
  }

  for(int s=0; s<size(segs); s++) {
    const auto& [i, j, k] = segs[s];
    int a = min(rank[i][j], rank[i][k]);
    int b = max(rank[i][j], rank[i][k]);
    for(int t=0; t<s; t++) {
      const auto& [ii, jj, kk] = segs[t];
      int c = min(rank[ii][jj], rank[ii][kk]);
      int d = max(rank[ii][jj], rank[ii][kk]);
      bool x = (a <= rank[i][ii] && rank[i][ii] <= b
          && c <= rank[ii][i] && rank[ii][i] <= d);
      intersect[i][j][k][ii][jj][kk] = x;
      intersect[ii][jj][kk][i][j][k] = x;
    }
  }

  vector<int> order;
  order.push_back(n-1);
  cout << solve((1<<(n-1)) - 1, order) / 2 << nl;

  return 0;
}
