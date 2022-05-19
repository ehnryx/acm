#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
//using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct pt {
  ll x, y;
  template <typename T>
  void fast_read(T& cin) { cin >> x >> y; }
  friend int imag(pt v) { return v.y; }
  friend pt conj(pt v) { return { v.x, -v.y }; }
  pt operator * (pt o) const { return { x*o.x - y*o.y, x*o.y + y*o.x }; }
  pt operator - (pt o) const { return { x - o.x, y - o.y }; }
};

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

bool collinear(const pt& a, const pt& b, const pt& c) {
  //return abs(cp(b - a, c - a) / abs(a - b)) < EPS;
  return abs(cp(b - a, c - a)) == 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  auto v = cin.read<pt>(n);

  if(n <= 3) {
    cout << "success" << nl;
    return 0;
  }

  const int M = 99;
  uniform_int_distribution<> distr(0, n - 1);

  bool ok = false;
  for(int iter=0; !ok && iter<M; iter++) {
    int s = distr(rng);
    int t = distr(rng);
    while(s == t) {
      t = distr(rng);
    }
    vector<pt> off;
    for(int i=0; i<n; i++) {
      if(!collinear(v[s], v[t], v[i])) {
        off.push_back(v[i]);
      }
    }
    bool good = true;
    for(int i=2; i<size(off); i++) {
      good &= collinear(off[0], off[1], off[i]);
    }
    ok |= good;
  }

  cout << (ok ? "success" : "failure") << nl;

  return 0;
}
