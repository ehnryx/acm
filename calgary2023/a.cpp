#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "geometry/lines.h"
%:include "geometry/polygon.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<int>;

struct circle {
  int x, y, r;
  operator pt() const { return pt(x, y); }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int w, h;
  cin >> w >> h;
  int n, m;
  cin >> n >> m;
  vector<circle> c;
  for(int i=0; i<n; i++) {
    int x, y, r;
    cin >> x >> y >> r;
    c.push_back({x, y, r});
  }
  while(m--) {
    int x, y;
    cin >> x >> y;
    vector p = { pt(x, y), pt(x, y+h), pt(x+w, y+h), pt(x+w, y) };
    bool ok =true;
    for(int k=0; k<n; k++) {
      ok &= not in_polygon(p, pt(c[k]));
      for(int i=3, j=0; j<4; i=j++) {
        ok &= segment_point_dist(p[i], p[j], pt(c[k])) > c[k].r;
      }
    }
    cout << "DOOMSLUG " << (ok ? "GO" : "STOP") << "!" << nl;
  }
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
