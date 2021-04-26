#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#define USE_INT128
// START #include "../../lca/numbers/fraction.h"

#ifdef USE_INT128
__int128 gcd(__int128 a, __int128 b) {
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
  fraction(const T& n = 0, const T& d = 1) {
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
  template <typename F> F value() const { return F(num) / F(den); }
};

// END #include "../../lca/numbers/fraction.h"

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

template <typename T> struct point {
  T x, y;
  point() = default;
  point(const T& _x, const T& _y): x(_x), y(_y) {}
  point operator + (const point& o) const { return point(x+o.x, y+o.y); }
  point operator - (const point& o) const { return point(x-o.x, y-o.y); }
  point operator * (const point& o) const { return point(x*o.x-y*o.y, x*o.y+y*o.x); }
  point operator * (const T& c) const { return point(x*c, y*c); }
  point operator / (const T& c) const { return point(x/c, y/c); }
  friend point operator * (const T& c, const point& v) {
    return point(c*v.x, c*v.y);
  }
  bool operator == (const point& o) const { return x == o.x && y == o.y; }
  friend ostream& operator << (ostream& os, const point& v) {
    return os << '(' << v.x << ',' << v.y << ')';
  }
  friend T abs(const point& v) { return sqrt(v.x*v.x + v.y*v.y); }
};

using P = point<F>;

template <typename T>
T cross(const point<T>& a, const point<T>& b) { return a.x*b.y - a.y*b.x; }

bool parallel(const point<F>& a, const point<F>& b, const point<F>& c, const point<F>& d) {
  return (a-b).x * (c-d).y == (a-b).y * (c-d).x;
}

bool parallel(const point<ld>& a, const point<ld>& b, const point<ld>& c, const point<ld>& d) {
  return abs(cross(a-b, c-d)) < EPS;
}

template <typename T>
point<T> line_inter(const point<T>& a, const point<T>& b, const point<T>& c, const point<T>& d) {
  return a + cross(c-a, d-c) / cross(b-a, d-c) * (b-a);
}

int sgn(const ld& v) { return v < -EPS ? -1 : EPS < v ? 1 : 0; }
int sgn(const F& v) { return v.num < 0 ? -1 : 0 < v.num ? 1 : 0; }

using F128 = fraction<__int128, true>;
int sgn_cross(const P& a, const P& b) {
  F128 left = F128(a.x) * F128(b.y);
  F128 right = F128(a.y) * F128(b.x);
  return left < right ? -1 : left > right ? 1 : 0;
}

bool seg_x_seg(const P& a, const P& b, const P& c, const P& d) {
  int r1 = sgn_cross(b-a, c-a), r2 = sgn_cross(b-a, d-a);
  int r3 = sgn_cross(d-c, a-c), r4 = sgn_cross(d-c, b-c);
  return r1*r2 <= 0 && r3*r4 <= 0;
}

const int N = 12;
pair<P,P> segment[N][N][N];
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
    lines.emplace_back(P(a, b), P(x, y));
  }

  vector<tuple<int,int,int>> sid;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(parallel(lines[i].first, lines[i].second, lines[j].first, lines[j].second)) continue;
      for(int k=0; k<n; k++) {
        if(parallel(lines[i].first, lines[i].second, lines[k].first, lines[k].second)) continue;
        P ij = line_inter(lines[i].first, lines[i].second, lines[j].first, lines[j].second);
        P ik = line_inter(lines[i].first, lines[i].second, lines[k].first, lines[k].second);
        if(ij == ik) continue;
        segment[i][j][k] = pair(ij, ik);
        exists[i][j][k] = true;
        sid.emplace_back(i, j, k);
      }
    }
  }

  for(int s=0; s<size(sid); s++) {
    const auto& [i, j, k] = sid[s];
    const auto& [a, b] = segment[i][j][k];
    for(int t=0; t<s; t++) {
      const auto& [ii, jj, kk] = sid[t];
      const auto& [c, d] = segment[ii][jj][kk];
      bool x = seg_x_seg(a, b, c, d);
      intersect[i][j][k][ii][jj][kk] = x;
      intersect[ii][jj][kk][i][j][k] = x;
    }
  }

  vector<int> order;
  order.push_back(n-1);
  cout << solve((1<<(n-1)) - 1, order) / 2 << nl;

  return 0;
}
