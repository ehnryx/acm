#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/nd_array.h"
//%:include "utility/output.h"

%:include "geometry/circle.h"

using ll = long long;
using ld = double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<circle<int>> circles;
  for(int i=0; i<n; i++) {
    int x, y, r;
    cin >> x >> y >> r;
    circles.emplace_back(x, y, r);
  }

  ld ans = 0;
  for(int i=0; i<n; i++) {
    bool covered = false;
    vector<pair<ld, int>> ev;
    for(int j=i+1; j<n; j++) {
      auto it = circles[i].intersect(circles[j], 1e-9);
      if(it.count() != 2) {
        if(circles[j].contains(circles[i].center) and circles[j].radius >= circles[i].radius) {
          covered = true;
          break;
        } else {
          continue;
        }
      }
      auto [u, v] = it.get_two();
      using I = decay_t<decltype(u)>;
      ld s = arg(u - I(circles[i].center));
      ld t = arg(v - I(circles[i].center));
      if(t < s) t += 2 * numbers::pi;
      ev.emplace_back(s, 1);
      ev.emplace_back(t, -1);
      ev.emplace_back(s + 2*numbers::pi, 1);
      ev.emplace_back(t + 2*numbers::pi, -1);
    }
    if(covered) continue;

    ev.emplace_back(numbers::pi, 0);
    ev.emplace_back(3*numbers::pi, 0);
    sort(begin(ev), end(ev));

    ld last_x = -numbers::pi;
    int depth = 0;
    for(auto [x, v] : ev) {
      if(depth == 0 and numbers::pi < x and x <= 3*numbers::pi) {
        ans += (x - last_x) * circles[i].radius;
      }
      depth += v;
      last_x = x;
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
