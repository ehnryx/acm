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
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<double>;

const auto PI = M_PIl;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, r;
  cin >> n >> r;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.emplace_back(x, y);
  }
  const pt O = pt(0, 0);

  double ans = 0;

  vector<double> circle;
  for(int i=n-1, j=0; j<n; i=j++) {
    auto ds = line_point_dist(p[i], p[j], O);
    if(ds >= r) continue;

    auto dir = p[j] - p[i];
    dir /= abs(dir);
    auto ndir = perp(dir);
    auto m = line_inter(p[i], p[j], O, ndir);
    double h = sqrt(r*r - ds*ds);
    auto a = m - dir * h;
    auto b = m + dir * h;
    if(abs(b - p[i]) < abs(a - p[i])) {
      swap(a, b);
    }

    vector<pt> line = {p[i]};
    for(auto x : {a, b}) {
      if(dot(x - p[i], p[j] - p[i]) > 0 and dot(x - p[j], p[i] - p[j]) > 0) {
        line.push_back(x);
        circle.push_back(arg(x));
      }
    }
    line.push_back(p[j]);
    for(int ii=0, jj=1; jj<size(line); ii=jj++) {
      auto mid = (line[ii] + line[jj]) / 2;
      if(norm(mid) < r*r) {
        ans += cross(line[ii], line[jj]);
      }
    }
  }

  assert(size(circle) % 2 == 0);
  sort(begin(circle), end(circle));
  for(int i=1; i<size(circle); i+=2) {
    ans += (circle[i] - circle[i-1]) * r * r;
  }

  cout << ans / 2 << nl;
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
