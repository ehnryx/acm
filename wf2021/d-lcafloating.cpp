#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "geometry/point.h"
%:include "geometry/lines.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-11L;
random_device _rd; mt19937 rng(_rd());

using pt = point<ld>;

int sgn(const ld& x, const ld& eps) {
  return x < -eps ? -1 : x > eps ? 1 : 0;
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
  static constexpr ld maxc = 2e3;

  auto is_inside = [&](int i, const pt& to) {
    int a = (i+1 == n ? 0 : i+1);
    int b = (i == 0 ? n-1 : i-1);
    if(cross(p[a] - p[i], p[b] - p[i]) >= 0) {
      return cross(p[a] - p[i], to - p[i]) >= -EPS and
        cross(to - p[i], p[b] - p[i]) >= -EPS;
    } else {
      return not (
          cross(p[a] - p[i], to - p[i]) < -EPS and
          cross(to - p[i], p[b] - p[i]) < -EPS);
    }
  };

  auto is_visible = [&](const pt& a, const pt& b) {
    bool left = true;
    bool right = true;
    for(int i=n-1, j=0; j<n; i=j++) {
      if(not parallel(EPS, a, b, p[i], p[j]) and seg_x_seg(EPS, a, b, p[i], p[j], true)) {
        return false;
      }
      ld ab = abs(b - a);
      int ci = sgn(cross(b - a, p[i] - a), ab * EPS);
      int cj = sgn(cross(b - a, p[j] - a), ab * EPS);
      bool oi = (dot(b - a, p[i] - a) > ab * EPS and
          dot(a - b, p[i] - b) > ab * EPS);
      bool oj = (dot(b - a, p[j] - a) > ab * EPS and
          dot(a - b, p[j] - b) > ab * EPS);
      if(ci == 0 and cj == 0 and (oi or oj)) {
        if(dot(p[j] - p[i], b - a) > 0) {
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

    pt far = p[t] + (p[t] - statue) * maxc;
    for(int i=n-1, j=0; j<n; i=j++) {
      if(i == t or j == t) continue;
      ld ij = abs(p[i] - p[j]);
      if(abs(cross(statue - p[t], p[j] - p[i])) < ij * EPS) {
        continue;
      }
      if(not parallel(EPS, far, p[t], p[i], p[j]) and seg_x_seg(EPS, far, p[t], p[i], p[j])) {
        pt it = line_inter(far, p[t], p[i], p[j]);
        if(abs(it - p[t]) < abs(far - p[t])) {
          far = it;
        }
      }
    }

    if(not is_visible(far, statue)) {
      continue;
    }

    for(int i=0; i<n; i++) {
      auto c = segment_closest(p[t], far, p[i]);
      if(is_inside(i, c) and is_visible(p[i], c)) {
        dist[n][i] = min(dist[n][i], abs(p[i] - c));
      }
    }
    auto c = segment_closest(p[t], far, guard);
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
