#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/nd_array.h"
//%:include "utility/output.h"

%:include "geometry/circle.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll sqr(ll x) { return x * x; }

struct Ring {
  array<circle<int>, 2> circles;
  Ring(int x, int y, int r_in, int r_out): circles{circle<int>(x, y, r_in), circle<int>(x, y, r_out)} {}
  const auto& inner() const { return circles[0]; }
  const auto& outer() const { return circles[1]; }
  bool contains(const circle<int>& o) const {
    const auto d2 = norm(circles[0].center - o.center);
    return \
      (sqr(inner().radius + o.radius) <= d2 and
       d2 <= sqr(outer().radius - o.radius) and outer().radius - o.radius >= 0) or
      (d2 <= sqr(min(o.radius - inner().radius, outer().radius - o.radius)) and
       min(o.radius - inner().radius, outer().radius - o.radius) >= 0);
  }
};

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<Ring> rings;
  for(int i=0; i<n; i++) {
    int x, y, D, d;
    cin >> x >> y >> D >> d;
    rings.emplace_back(x, y, max(0, D-d), D+d);
  }

  ld ans = 0;

  for(int i=0; i<n; i++) {
    for(int ci=0; ci<2; ci++) {
      auto circ = rings[i].circles[ci];
      if(circ.radius == 0) continue;

      bool covered = false;
      vector<tuple<ld, int, int>> ev;
      for(int j=0; j<n; j++) {
        if(i == j) continue;
        if(i < j and circ == rings[j].circles[ci]) {
          // not covered
        } else if(rings[j].contains(circ)) {
          covered = true;
          break;
        }
        {
          auto it = circ.intersect(rings[j].outer());
          if(it.count() == 2) {
            auto [u, v] = it.get_two();
            using I = decay_t<decltype(u)>;
            ev.emplace_back(arg(u - I(circ.center)), 1, j);
            ev.emplace_back(arg(v - I(circ.center)), -1, j);
          }
        }
        if(rings[j].inner().radius > 0) {
          auto it = circ.intersect(rings[j].inner());
          if(it.count() == 2) {
            auto [u, v] = it.get_two();
            using I = decay_t<decltype(u)>;
            ev.emplace_back(arg(u - I(circ.center)), -1, j);
            ev.emplace_back(arg(v - I(circ.center)), 1, j);
          }
        }
      }
      if(covered) continue;

      ev.emplace_back(0, 0, -1);
      ev.emplace_back(numbers::pi, 0, -1);
      sort(begin(ev), end(ev));

      set<int> have;
      for(auto [_, s, idx] : ev) {
        if(s > 0) {
          have.insert(idx);
        } else {
          have.erase(idx);
        }
      }

      int depth = size(have);
      ld last_x = -numbers::pi;
      for(auto [x, s, _] : ev) {
        if(depth == 0) {
          static constexpr ld BOTTOM = -2000;
          auto u = circ.get_point(last_x);
          auto v = circ.get_point(x);
          auto trapezoid = abs(u.x - v.x) * (u.y - BOTTOM + v.y - BOTTOM) / 2;
          auto segment = circ.segment_area(x - last_x);
          assert(trapezoid >= 0);
          assert(segment >= 0);
          if(x <= 0) {
            int sign = (ci == 1 ? -1 : 1);
            ans += (trapezoid - segment) * sign;
          } else {
            int sign = (ci == 1 ? 1 : -1);
            ans += (trapezoid + segment) * sign;
          }
        }
        depth += s;
        last_x = x;
      }
    }
  }

  cout << "Case " << testnum << ": ";
  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
