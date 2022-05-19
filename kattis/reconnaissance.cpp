#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

using ll = long long;
using ld = /*long*/ double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  auto lines = cin.read<pair<int, int>>(n);

  function<ld(ld)> calc = [=](ld t) {
    ld l = 1e42;
    ld r = -1e42;
    for(auto [x, v] : lines) {
      ld y = x + v * t;
      l = min(l, y);
      r = max(r, y);
    }
    assert(l <= r);
    return r - l;
  };

  const ld phi = (sqrt(5) + 1) / 2;

  ld l = 0;
  ld r = 2e5 + 7;

  ld lm = (phi*l + r) / (1 + phi);
  ld rm = (l + phi*r) / (1 + phi);
  ld lv = calc(lm);
  ld rv = calc(rm);

  for(int bs=0; bs<42; bs++) {
    if(lv < rv) {
      r = rm;
      rm = lm;
      rv = lv;
      lm = (phi*l + r) / (1 + phi);
      lv = calc(lm);
    } else {
      l = lm;
      lm = rm;
      lv = rv;
      rm = (l + phi*r) / (1 + phi);
      rv = calc(rm);
    }
  }

  /*
  for(int bs=0; bs<42; bs++) {
    ld lm = (5*l + 4*r) / 9;
    ld rm = (4*l + 5*r) / 9;
    if(calc(lm) < calc(rm)) {
      r = rm;
    } else {
      l = lm;
    }
  }
  */

  cout << calc(r) << nl;

  return 0;
}
