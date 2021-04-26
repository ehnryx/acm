#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

template <typename T>
T gcd(T a, T b) { return abs(__gcd(a, b)); }

// START #include "../../lca/numbers/fraction.h"

template <typename T, bool overflow_guard = false>
struct fraction {
  T num, den;
  fraction(const T& n = 0, const T& d = 1) {
    T g = gcd(n, d);
    num = d < 0 ? -n/g : n/g;
    den = d < 0 ? -d/g : d/g;
  }
  fraction(const pair<T, T>& f): num(f.first), den(f.second) {} // skip gcd
  const T& numerator() const { return num; }
  const T& denominator() const { return den; }
  T floor() const { return num < 0 ? (num - den + 1) / den : num / den; }
  friend ostream& operator << (ostream& os, const fraction<T>& v) {
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
    num *= o.num / gcd(o.num, den);
    den *= o.den / gcd(o.den, num);
    return *this;
  }
  fraction& operator /= (const fraction& o) {
    num *= o.den / gcd(o.den, den);
    den *= o.num / gcd(o.num, num);
    return *this;
  }
  bool operator < (const fraction& o) const {
    if (den == 0 && o.den == 0) return num && o.num && num < o.num;
    if (den == 0) return num < 0;
    if (o.den == 0) return 0 < o.num;
    if (overflow_guard) {
      T y = floor();
      T oy = o.floor();
      if (y != oy) return y < oy;
      return compare_fractions(num - den * y, den, o.num - o.den * oy, o.den);
    } else {
      return num * o.den < o.num * den;
    }
  }
  bool compare_fractions(const T& a, const T& b, const T& c, const T& d) {
    if (b == d || a == 0 || c == 0) return a < c;
    return 2*a > b && 2*c > d ? fraction(d-c, d) < fraction(b-a, b) :
      fraction(d, c) < fraction(b, a);
  }
  bool operator > (const fraction& o) const { return o < *this; }
  bool operator == (const fraction& o) const { return num == o.num && den == o.den; }
  bool operator <= (const fraction& o) const { return operator == (o) || operator < (o); }
  bool operator >= (const fraction& o) const { return o <= *this; }
};

// END #include "../../lca/numbers/fraction.h"

//#define FILENAME sadcactus

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
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



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

  int T;
  cin >> T;
  while(T--) {
    int a, b;
    cin >> a >> b;
    fraction<ll> f(a, b);
    if (f.den == 0) {
      cout << "the denominator can not be zero" << nl;
    } else if (f.den == 1) {
      cout << f.num << nl;
    } else {
      cout << f.num << " " << f.den << nl;
    }
  }

  return 0;
}

