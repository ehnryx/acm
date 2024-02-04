%:include "geometry/lines.h"
using pt = point<int>;

#define MULTI_TEST
%:include "main.h"
SOLVE() {
  int n;
  cin >> n;
  vector<pt> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    p[i] *= 2;
  }

  if (n == 1) {
    cout << "YES" << nl;
    return void(cout << p.back() / 2 << nl);
  }

  static vector<pt> const directions = {
      pt(1, 0),
      pt(0, 1),
      pt(1, 1),
      pt(1, -1),
  };

  auto is_valid = [&](pt a, pt b) {
    for (auto d : directions) {
      if (cross(a - b, d) == 0) {
        return true;
      }
    }
    return false;
  };

  auto get_inter = [&](pt a, pt b, pt c, pt d) {
    auto it = line_inter(a, b, c, d);
    return pt(round(it.x), round(it.y));
  };

  auto get_candidates = [&](pt a, pt b) {
    vector<pt> candidates;
    for (auto da : directions) {
      for (auto db : directions) {
        if (cross(da, db) == 0) continue;
        auto it = get_inter(a, a + da, b, b + db);
        if (it.x % 2 == 0) candidates.push_back(it);
      }
    }
    return candidates;
  };

  vector<pt> candidates = get_candidates(p[0], p[1]);
  if (is_valid(p[0], p[1])) {
    bool line = true;
    for (int i = 2; i < n; i++) {
      if (not collinear(p[0], p[1], p[i])) {
        line = false;
        vector<pt> new_cs;
        for (auto v : candidates) {
          if (is_valid(v, p[i])) {
            new_cs.push_back(v);
          }
        }
        for (auto d : directions) {
          if (cross(d, p[0] - p[1]) == 0) continue;
          auto it = get_inter(p[0], p[1], p[i], p[i] + d);
          if (it.x % 2 == 0) new_cs.push_back(it);
        }
        candidates = move(new_cs);
        break;
      }
    }
    if (line) {
      cout << "YES" << nl;
      return void(cout << p.back() / 2 << nl);
    }
  }

  for (int i = 0; i < n; i++) {
    vector<pt> new_cs;
    for (auto v : candidates) {
      if (is_valid(v, p[i])) {
        new_cs.push_back(v);
      }
    }
    candidates = move(new_cs);
  }
  if (empty(candidates)) {
    cout << "NO" << nl;
  } else {
    cout << "YES" << nl;
    cout << candidates.back() / 2 << nl;
  }
}
