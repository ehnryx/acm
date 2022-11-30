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

struct Point {
  int x, y, i;
  Point(int _x, int _y, int _i): x(_x), y(_y), i(_i) {}
  bool operator < (const Point& o) const {
    if(x != o.x) return x < o.x;
    if(left() != o.left()) return y < o.y;
    if(y != o.y) return y > o.y;
    return left() ? i < o.i : i > o.i;
  }
  bool left() const {
    return x < y;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  vector<Point> all, orig;
  for(int i=0; i<n; i++) {
    int s, d, p;
    cin >> s >> d >> p;
    orig.emplace_back(s, s + d, p);
    all.emplace_back(s, s + d, i);
    all.emplace_back(s + d, s, i);
  }

  sort(begin(all), end(all));

  for(int i=0; i<size(all); i++) {
    auto [l, r, idx] = all[i];
    if(l < r) {
      orig[idx].x = i;
    } else {
      orig[idx].y = i;
    }
  }

  vector dp(2*n, vector<int>(2*n, -1));
  auto solve = [&](auto& self, int l, int r) -> int {
    if(l >= r) return 0;
    if(dp[l][r] != -1) return dp[l][r];
    int res = self(self, l+1, r);
    if(int i = all[l].i; all[l].x < all[l].y && orig[i].y <= r) {
      // if x < y and index of y is in range
      res = max(res, orig[i].i + self(self, l+1, orig[i].y - 1) + self(self, orig[i].y + 1, r));
    }
    return dp[l][r] = res;
  };

  cout << solve(solve, 0, 2*n-1) << nl;

  return 0;
}
