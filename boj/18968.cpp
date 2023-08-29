#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

constexpr ld PI = numbers::pi_v<ld>;

ld get_angle(auto&& radius, ld r) {
  ld total = 0;
  for(auto R : radius) {
    total += acos(r/2 / R);
  }
  return total;
}

ld get_smallest(auto&& radius) {
  return get_angle(radius, 2 * radius.back());
}

ld solve(auto&& radius) {
  ld l = 0;
  ld r = 2 * radius.back();
  for(int bs=0; bs<99; bs++) {
    ld m = (l + r) / 2;
    if(get_angle(radius, m) > PI) {
      l = m;
    } else {
      r = m;
    }
  }

  ld ans = 0;
  for(auto R : radius) {
    ld angle = 2 * acos(r/2 / R);
    ld inner = PI - angle;
    ld circular = (PI - inner) * R * R;
    ld triangular = sin(inner) * R * R;
    ans += circular + triangular;
  }
  return ans;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> radius(n);
  for(int i=0; i<n; i++) {
    cin >> radius[i];
  }

  if(n <= 2) {
    ld ans = 0;
    for(auto R : radius) {
      ans += PI * R * R;
    }
    return void(cout << ans << nl);
  }

  sort(begin(radius), end(radius), greater<>());

  int l = 3;
  int r = n;
  while(l < r) {
    int m = (l + r + 1) / 2;
    if(get_smallest(radius | views::take(m)) < PI) {
      l = m;
    } else {
      r = m - 1;
    }
  }

  cout << solve(radius | views::take(r)) << nl;
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
