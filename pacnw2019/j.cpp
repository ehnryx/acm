#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
//using ld = long double;
using ld = double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  ld full = numbers::pi_v<ld> * 2;

  auto get = [](ld x, ld m, ld xint) -> tuple<ld, ld, ld> {
    return tuple(x, m, -m * xint);
  };

  int n;
  cin >> n;
  ld M = 0, B = 0;
  vector<tuple<ld, ld, ld>> lines;
  for(int i=0; i<n; i++) {
    ld t, s, a;
    cin >> t >> s >> a;
    if(s == 0) {
      B += t;
    } else {
      ld radius = t / s;
      if (radius >= numbers::pi) {
        B += t - s * numbers::pi;
        t = s * numbers::pi;
        radius = numbers::pi;
      }
      lines.emplace_back(get(a - radius, s, a - radius));
      lines.emplace_back(get(a, -s * 2, a));
      lines.emplace_back(get(a + radius, s, a + radius));
      lines.emplace_back(get(full + a - radius, s, full + a - radius));
      lines.emplace_back(get(full + a, -s * 2, full + a));
      lines.emplace_back(get(full + a + radius, s, full + a + radius));
    }
  }
  sort(begin(lines), end(lines));

  ld ans = 0;
  for(auto [x, m, b] : lines) {
    M += m;
    B += b;
    ans = max(ans, M * x + B);
  }
  cout << ans << nl;

  return 0;
}
