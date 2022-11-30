#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/fraction.h"
%:include "geometry/point.h"
%:include "geometry/lines.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
random_device _rd; mt19937 rng(_rd());

using pt = point<int>;

int sgn(const auto& x) {
  return x < 0 ? -1 : x > 0 ? 1 : 0;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  auto read_pt = [&] {
    int x, y;
    cin >> x >> y;
    return pt(x, y);
  };
  vector<pt> p;
  for(int i=0; i<n; i++) {
    p.push_back(read_pt());
  }
  auto guard = read_pt();
  auto statue = read_pt();

  static constexpr ld big = 1e9;
  static constexpr int maxc = 2e3;

  auto is_inside = [&](int i, const auto& to) {
    using F = typename decay_t<decltype(to)>::Type;
    int a = (i+1 == n ? 0 : i+1);
    int b = (i == 0 ? n-1 : i-1);
    if(cross(p[a] - p[i], p[b] - p[i]) >= 0) {
      return cross<F>(p[a] - p[i], to - p[i]) >= 0 and cross<F>(to - p[i], p[b] - p[i]) >= 0;
    } else {
      return not (cross<F>(p[a] - p[i], to - p[i]) < 0 and cross<F>(to - p[i], p[b] - p[i]) < 0);
    }
  };

  auto is_visible = [&](const auto& a, const auto& b) {
    using F = typename decltype(b - a)::Type;
    bool left = true;
    bool right = true;
    for(int i=n-1, j=0; j<n; i=j++) {
      if(not parallel<F>(a, b, p[i], p[j]) and seg_x_seg<F>(a, b, p[i], p[j], true)) {
        return false;
      }
      int ci = sgn(cross<F>(b - a, p[i] - a));
      int cj = sgn(cross<F>(b - a, p[j] - a));
      bool oi = (dot<F>(b - a, p[i] - a) > 0 and dot<F>(a - b, p[i] - b) > 0);
      bool oj = (dot<F>(b - a, p[j] - a) > 0 and dot<F>(a - b, p[j] - b) > 0);
      if(ci == 0 and cj == 0 and (oi or oj)) {
        if(dot<F>(p[j] - p[i], b - a) > 0) {
          right = false;
        } else {
          left = false;
        }
      } else if(ci == 0 and oi) {
        if(cj < 0) {
          right = false;
        } else {
          left = false;
        }
      } else if(cj == 0 and oj) {
        if(ci < 0) {
          right = false;
        } else {
          left = false;
        }
      }
    }
    return left or right;
  };

  if(is_visible(guard, statue)) {
    cout << 0 << nl;
    return;
  }

  ld ans = big;
  vector dist(n+1, vector(n+1, big));

  for(int t=0; t<n; t++) {
    if(not is_visible(p[t], statue)) {
      continue;
    }
    dist[n][t] = 0;

    if(not is_inside(t, p[t] + p[t] - statue)) {
      continue;
    }

    pt inf = p[t] + (p[t] - statue) * maxc;
    point<pt::Inter> far = inf;
    for(int i=n-1, j=0; j<n; i=j++) {
      if(i == t or j == t) continue;
      if(abs(cross(statue - p[t], p[j] - p[i])) < 0) {
        continue;
      }
      if(not parallel(inf, p[t], p[i], p[j]) and seg_x_seg(inf, p[t], p[i], p[j])) {
        auto it = line_inter(inf, p[t], p[i], p[j]);
        if(abs(it - p[t]) < abs(far - p[t])) {
          far = it;
        }
      }
    }

    if(not is_visible(far, statue)) {
      continue;
    }

    for(int i=0; i<n; i++) {
      auto c = segment_closest<pt::Inter>(p[t], far, p[i]);
      if(is_inside(i, c) and is_visible(p[i], c)) {
        dist[n][i] = min(dist[n][i], abs(p[i] - c));
      }
    }
    auto c = segment_closest<pt::Inter>(p[t], far, guard);
    if(is_visible(guard, c)) {
      ans = min(ans, abs(guard - c));
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      if(is_inside(i, p[j]) and is_visible(p[i], p[j])) {
        dist[i][j] = dist[j][i] = abs(p[i] - p[j]);
      }
    }
  }

  for(int k=0; k<=n; k++) {
    for(int i=0; i<=n; i++) {
      for(int j=0; j<=n; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  for(int i=0; i<n; i++) {
    if(is_visible(guard, p[i])) {
      ans = min(ans, abs(guard - p[i]) + dist[n][i]);
    }
  }

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
