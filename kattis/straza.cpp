#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"

%:include "number/fraction.h"

using ll = long long;
using ld = long double;
//using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

/*
struct fa {
  ll n, d;
  fa(ll _n=0, ll _d=1): n(_n), d(_d) {
    ll g = abs(gcd(n, d));
    n /= g;
    d /= g;
    assert(d > 0);
  }
  bool operator < (const fa& o) const { return n*o.d < d*o.n; }
  bool operator == (const fa& o) const { return n == o.n && d == o.d; }
  bool operator <= (const fa& o) const { return operator < (o) || operator == (o); }
  fa operator - () const { return fa(-n, d); }
  fa operator + (const fa& o) const { return fa(n*o.d + d*o.n, d*o.d); }
  fa operator - (const fa& o) const { return fa(n*o.d - d*o.n, d*o.d); }
  fa operator * (const fa& o) const { return fa(n*o.n, d*o.d); }
  fa operator / (const fa& o) const {
    return o.n > 0 ? fa(n*o.d, d*o.n) : fa(-n*o.d, -d*o.n);
  }
  fa& operator += (const fa& o) { return *this = operator + (o); }
  fa& operator -= (const fa& o) { return *this = operator - (o); }
  fa& operator *= (const fa& o) { return *this = operator * (o); }
  fa& operator /= (const fa& o) { return *this = operator / (o); }
  friend ostream& operator << (ostream& os, const fa& v) {
    return os << v.n << "/" << v.d;
  }
};
*/

using fa = fraction<ll>;

using pt = complex<fa>;

bool operator < (pt a, pt b) {
  return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag());
}

bool operator <= (pt a, pt b) {
  return a < b || a == b;
}

fa cp(pt a, pt b) { return imag(conj(a) * b); }
fa dp(pt a, pt b) { return real(conj(a) * b); }

pt line_inter(pt a, pt b, pt c, pt d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;

  vector<pair<pt, pt>> segs;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    pt u = min(pt(fa(a), fa(b)), pt(x, y));
    pt v = max(pt(a, b), pt(x, y));
    if (u == v) continue;
    while(true) {
      bool found = false;
      for(auto it = begin(segs); it != end(segs); it++) {
        if(cp(u - v, it->second - v) == 0 && cp(u - v, it->first - v) == 0 &&
            u <= it->second && it->first <= v) {
          u = min(u, it->first);
          v = max(v, it->second);
          segs.erase(it);
          found = true;
          break;
        }
      }
      if(!found) {
        segs.emplace_back(u, v);
        break;
      }
    }
  }
  n = size(segs);

  vector<pt> its;
  for(int i=0; i<n; i++) {
    auto [a, b] = segs[i];
    for(int j=0; j<i; j++) {
      auto [c, d] = segs[j];
      if(cp(a - b, c - d) == 0) continue;
      pt it = line_inter(a, b, c, d);
      if(a <= it && it <= b && c <= it && it <= d) {
        its.push_back(it);
      }
    }
  }
  sort(begin(its), end(its));
  its.resize(unique(begin(its), end(its)) - begin(its));

  vector<int> ons(size(its));
  for(int i=0; i<size(its); i++) {
    for(int j=0; j<n; j++) {
      auto [a, b] = segs[j];
      if(cp(a - b, its[i] - b) == 0 && fa(0) <= dp(its[i] - a, b - a) && fa(0) <= dp(its[i] - b, a - b)) {
        ons[i] |= 1 << j;
      }
    }
  }

  int ans = 0;
  for(int i=0; i<size(its); i++) {
    for(int j=0; j<i; j++) {
      for(int k=0; k<j; k++) {
        int ij = ons[i] & ons[j];
        int jk = ons[j] & ons[k];
        int ki = ons[k] & ons[i];
        if(ij && jk && ki && ij != jk && jk != ki && ki != ij) {
          ans++;
        }
      }
    }
  }

  cout << ans << nl;

  return 0;
}
