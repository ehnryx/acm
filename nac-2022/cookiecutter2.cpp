#include <bits/stdc++.h>
using namespace std;

%:include "utility/defines.h"
%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "geometry/point.h"
%:include "geometry/lines.h"
%:include "geometry/polygon.h"

using ll = long long;
using ld = double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<int>;

ld get_area(point<double> pivot, point<double> dir, const vector<pt>& box) {
  return abs(signed_area(cut_polygon(EPS, polygon<double>(box), pivot, pivot + dir)));
}

ld calc_area(ld angle, point<double> pivot, const vector<pt>& box) {
  return get_area(pivot, point<double>::polar(1, angle), box);
}

struct ray {
  int y, x, s, add;
  bool operator < (const ray& o) const {
    if(s != o.s) return s < o.s;
    // (y/x < o.y/o.x)
    return y*o.x < o.y*x;
  }
};

ld solve(int len, const vector<pt>& all, int base) {
  const vector<pt> box = { pt(0, 0), pt(len, 0), pt(len, len), pt(0, len) };
  int n = size(all);
  ld ans = 0;

  // one
  vector<ld> args;
  for(pt corner : box) {
    args.push_back(arg(corner - all[base]));
    args.push_back(arg(all[base] - corner));
  }
  sort(begin(args), end(args));
  args.push_back(args.front() + 2*M_PIl);
  for(int s=1; s<size(args); s++) {
    ld l = args[s-1];
    ld r = args[s];
    for(int bs=0; bs<99; bs++) {
      ld lm = (5*l + 4*r) / 9;
      ld rm = (4*l + 5*r) / 9;
      if(calc_area(lm, all[base], box) < calc_area(rm, all[base], box)) {
        r = rm;
      } else {
        l = lm;
      }
    }
    point<double> dir = point<double>::polar(1, r);
    int cnt = 0;
    for(pt v : all) {
      cnt += (dir.cross(v - all[base]) >= 0);
    }
    ans = max(ans, (ld)cnt/n - calc_area(r, all[base], box) / (len*len));
  }

  // two
  vector<ray> rot;
  int cnt = 1;
  for(int i=0; i<n; i++) {
    if(i == base) continue;
    pt dir = all[i] - all[base];
    int add = 1;
    if(dir < pt(0, 0)) {
      dir = -dir;
      add = -1;
    } else {
      cnt++;
    }
    rot.push_back({ dir.y, dir.x, 0, -add });
    rot.push_back({ dir.y, dir.x, 1, add });
  }
  sort(begin(rot), end(rot));
  for(auto [y, x, s, add] : rot) {
    cnt += add;
    pt dir(x, y);
    if(s) dir = -dir;
    ans = max(ans, (ld)cnt/n - get_area(all[base], dir, box) / (len*len));
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  auto v = cin.read<pt>(m);

  ld ans = 0;
  for(int i=0; i<m; i++) {
    ans = max(ans, solve(n, v, i));
  }
  cout << ans << nl;

  return 0;
}
