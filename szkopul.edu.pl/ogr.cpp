#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "utility/nd_array.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
//random_device _rd; mt19937 rng(_rd());

struct Point {
  int x, y;
  int value;
  bool operator<(const Point& o) const {
    return x < o.x or (x == o.x and y < o.y);
  }
  Point operator-(const Point& o) const {
    return Point{x - o.x, y - o.y, 0};
  }
};

ll cross(const Point& a, const Point& b) {
  return (ll)a.x * b.y - (ll)b.x * a.y;
}

struct Segment {
  int ri, li;
  Point dir;
  bool operator<(const Segment& o) const {
    return cross(dir, o.dir) > 0;
  }
};

static constexpr auto BIG = numeric_limits<ll>::max() / 4;

void update_max(ll& old, ll base, ll add) {
  if(base == -BIG) return;
  old = max(old, base + add);
}

void update_min(ll& old, ll base, ll add) {
  if(base == BIG) return;
  old = min(old, base + add);
}

nd_array<ll, 3> solve_upper(const vector<Point>& p, const nd_array<ll, 2>& mass) {
  const int n = size(p);
  vector<Segment> segs;
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      segs.push_back(Segment{i, j, p[i] - p[j]});
    }
  }
  sort(begin(segs), end(segs));
  reverse(begin(segs), end(segs));

  nd_array<ll, 3> dp(n, n, 2, -BIG);
  for(const auto& s : segs) {
    auto value = mass(s.ri, s.li) + p[s.ri].value;
    dp(s.ri, s.li, 0) = mass(s.li, s.li) + p[s.li].value + value;
    for(int i=0; i<s.li; i++) {
      update_max(dp(s.ri, i, 1), dp(s.li, i, 0), value);
      update_max(dp(s.ri, i, 1), dp(s.li, i, 1), value);
    }
  }
  return dp;
}

nd_array<ll, 3> solve_lower(const vector<Point>& p, const nd_array<ll, 2>& mass) {
  const int n = size(p);
  vector<Segment> segs;
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      segs.push_back(Segment{i, j, p[i] - p[j]});
    }
  }
  sort(begin(segs), end(segs));

  nd_array<ll, 3> dp(n, n, 2, BIG);
  for(const auto& s : segs) {
    auto value = mass(s.ri, s.li);
    dp(s.ri, s.li, 0) = mass(s.li, s.li) + value;
    for(int i=0; i<s.li; i++) {
      update_min(dp(s.ri, i, 1), dp(s.li, i, 0), value);
      update_min(dp(s.ri, i, 1), dp(s.li, i, 1), value);
    }
  }
  return dp;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<Point> p;
  for(int i=0; i<n; i++) {
    int x, y, value;
    cin >> x >> y >> value;
    p.push_back(Point{x, y, value});
  }
  sort(begin(p), end(p));

  nd_array<ll, 2> mass(n, n);
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      for(int k=0; k<n; k++) {
        if(not (p[j].x < p[k].x and p[k].x <= p[i].x)) continue;
        if(cross(p[i] - p[k], p[j] - p[k]) <= 0) continue;
        mass(i, j) += p[k].value;
      }
      if(p[j].x == p[i].x) {
        mass(i, i) += p[j].value;
      }
    }
  }

  auto upper = solve_upper(p, mass);
  auto lower = solve_lower(p, mass);

  ll ans = -BIG;
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      ans = max(ans, upper(i, j, 0) - lower(i, j, 1));
      ans = max(ans, upper(i, j, 1) - lower(i, j, 0));
      ans = max(ans, upper(i, j, 1) - lower(i, j, 1));
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
