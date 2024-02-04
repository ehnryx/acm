#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ll = long long;
using ld = long double;

struct Segment {
  int l, r, h;
  friend auto operator>>(istream& is, Segment& v) -> istream& {
    return is >> v.l >> v.r >> v.h;
  }
};

struct Point {
  int x, y;
  auto operator-(Point const& o) const -> Point { return {x - o.x, y - o.y}; }
};

struct Function {
  ll mm, mb, bb, m, b, c;
  auto add(Segment const& s) -> void {
    // x = slope * s.h + intercept
    // (s.l - x) * (x - s.r)
    mm += -s.h * s.h;
    bb += -1;
    mb += -2 * s.h;
    m += s.h * (s.l + s.r);
    b += s.l + s.r;
    c += -s.l * s.r;
  }
  auto eval(ld slope, ld intercept) const -> ld {
    return mm * slope * slope + bb * intercept * intercept + mb * slope * intercept +
           m * slope + b * intercept + c;
  }
  auto solve() const -> ld {
    // dslope: 2 * mm * slope + mb * intercept + m = 0
    // dinter: 2 * bb * inter + mb * slope + b = 0
    // slope = (2 * bb * inter + b) / -mb
    // 2 * mm * (2 * bb * inter + b) / -mb + mb * inter + m = 0
    // (mb - 4 * mm * bb / mb) * inter = 2 * mm * b / mb - m
    ld const intercept = ((ld)2 * mm * b / mb - m) / (mb - (ld)4 * mm * bb / mb);
    ld const slope = (2 * bb * intercept + b) / -mb;
    return eval(slope, intercept);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  auto segs = vector<Segment>(n);
  auto ps = vector<Point>();
  for (int i = 0; i < n; i++) {
    cin >> segs[i];
    ps.emplace_back(segs[i].l, segs[i].h);
    ps.emplace_back(segs[i].r, segs[i].h);
  }

  ld ans = 0;
  for (auto const& cur : segs) {
    auto dx = cur.l - cur.r;
    ans = max(ans, dx * dx / (ld)4);
  }

  for (int i = 0; i < size(ps); i++) {
    for (int j = 0; j < i; j++) {
      if (ps[i].y == ps[j].y) continue;
      auto line = (ps[i].y > ps[j].y ? ps[i] - ps[j] : ps[j] - ps[i]);
      auto f1 = Function();
      auto f2 = Function();
      for (int si = 0; si < size(segs); si++) {
        auto const& cur = segs[si];
        auto x_sy = ps[i].x * line.y + (cur.h - ps[i].y) * line.x;
        if (cur.l * line.y <= x_sy and x_sy < cur.r * line.y) {
          f1.add(cur);
        }
        if (cur.l * line.y < x_sy and x_sy <= cur.r * line.y) {
          f2.add(cur);
        }
      }
      ans = max(ans, f1.solve());
      ans = max(ans, f2.solve());
    }
  }

  cout << ans << nl;

  return 0;
}
