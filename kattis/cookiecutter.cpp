#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

ld area(const auto& v) {
  int n = size(v);
  ld res = 0;
  for(int i=n-1, j=0; j<n; i=j++) {
    res += cp(v[i], v[j]);
  }
  return abs(res) / 2;
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
  int goal;
  cin >> goal;

  ld have = area(v);
  ld f = sqrt(goal / have);
  ld minx = 1e42;
  ld miny = 1e42;
  for(pt& it : v) {
    it *= f;
    minx = min(minx, it.real());
    miny = min(miny, it.imag());
  }

  for(pt& it : v) {
    it -= pt(minx, miny);
    cout << it.real() << " " << it.imag() << nl;
  }

  return 0;
}
