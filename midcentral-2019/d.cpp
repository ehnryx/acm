%:include "geometry/circle.h"
%:include "main.h"
#include <algorithm>
SOLVE() {
  int n;
  cin >> n;
  vector<circle<ll>> cs;
  for (int i = 0; i < n; i++) {
    int x, y, r;
    cin >> x >> y >> r;
    cs.emplace_back(x, y, r);
  }
  int b, d;
  cin >> b >> d;
  for (auto& c : cs) {
    c.radius += b;
  }
  circle<ll> O(0, 0, d);

  using ld = double;
  vector<pair<ld, int>> ev;

  //using namespace numbers;
  static const auto pi = acos((ld)-1);
  auto add_seg = [&](ld s, ld t) {
    if (s > t) t += 2 * pi;
    assert(s <= t);
    while (s < 0) {
      s += 2 * pi;
      t += 2 * pi;
    }
    ev.emplace_back(s, 1);
    ev.emplace_back(t, -1);
    ev.emplace_back(s + 2 * pi, 1);
    ev.emplace_back(t + 2 * pi, -1);
  };

  for (auto const& c : cs) {
    auto h = norm(c.center) - c.radius * c.radius;
    if (h < O.radius * O.radius) {
      auto mid = arg(c.center);
      auto ra = asin(c.radius / abs(c.center));
      add_seg(mid - ra, mid + ra);
    } else {
      auto it = O.intersect(c);
      if (it.count() < 2) continue;
      auto [l, r] = it.get_two();
      add_seg(arg(l), arg(r));
    }
  }

  ev.emplace_back(2 * pi, 0);
  ev.emplace_back(4 * pi, 0);

  sort(begin(ev), end(ev));

  ld last_x = 0;
  int cnt = 0;
  ld ans = 0;
  for (auto [x, add] : ev) {
    if (2 * pi <= last_x and x <= 4 * pi and cnt == 0) {
      ans += x - last_x;
    }
    cnt += add;
    last_x = x;
  }
  cout << ans / (2 * pi) << nl;
}
