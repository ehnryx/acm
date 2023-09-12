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

struct pt {
  int x, y;
  bool operator<(pt o) const { return x < o.x or (x == o.x and y < o.y); }
  bool operator==(pt o) const { return x == o.x and y == o.y; }
  pt operator-(pt o) const { return pt{ x - o.x, y - o.y }; }
  friend ostream& operator<<(ostream& os, pt v) { return os << v.x << " " << v.y; }
};
ll cross(pt a, pt b) {
  return (ll)a.x * b.y - (ll)a.y * b.x;
}
ll dot(pt a, pt b) {
  return (ll)a.x * b.x + (ll)a.y * b.y;
}

vector<pt> convex_hull(vector<pt> p) {
  sort(begin(p), end(p));
  int n = size(p);
  vector<pt> h;
  for(int i=0; i<n; i++) {
    while(size(h)>=2 and cross(h[size(h)-2] - p[i], h[size(h)-1] - p[i]) <= 0) {
      h.pop_back();
    }
    h.push_back(p[i]);
  }
  for(int i=n-2; i>=0; i--) {
    while(size(h)>=2 and h.back() != p.back() and
        cross(h[size(h)-2] - p[i], h[size(h)-1] - p[i]) <= 0) {
      h.pop_back();
    }
    h.push_back(p[i]);
  }
  h.pop_back();
  return h;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  // start 21:00
  int n, k;
  cin >> n >> k;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.emplace_back(x, y);
  }

  auto outer = convex_hull(p);
  auto inner = convex_hull(vector(begin(p), begin(p) + k));

  int m = size(inner);
  vector<ll> area(2*m);
  for(int i=0; i<2*m; i++) {
    int r = i < m ? i : i - m;
    int l = r > 0 ? r-1 : m-1;
    area[i] = cross(inner[l], inner[r]);
  }
  partial_sum(begin(area), end(area), begin(area));
  ll base = area[m] - area[0];

  auto left_cond = [&](int i, pt v) {
    int pi = (i>0 ? i-1 : m-1);
    int ni = (i+1<m ? i+1 : 0);
    return (cross(inner[i] - v, inner[pi] - v) < 0 and
        cross(inner[i] - v, inner[ni] - v) <= 0);
  };

  auto right_cond = [&](int i, pt v) {
    int pi = (i>0 ? i-1 : m-1);
    int ni = (i+1<m ? i+1 : 0);
    return (cross(inner[i] - v, inner[ni] - v) > 0 and
        cross(inner[i] - v, inner[pi] - v) >= 0);
  };

  int l = -1, r = -1;
  for(int i=0; i<m; i++) {
    if(left_cond(i, outer[0])) {
      l = i;
    }
    if(right_cond(i, outer[0])) {
      r = i;
    }
  }
  assert(l != -1 and r != -1);

  ll ans = base;
  for(int i=0; i<size(outer); i++) {
    while(not left_cond(l, outer[i])) {
      l = (l+1<m ? l+1 : 0);
    }
    while(not right_cond(r, outer[i])) {
      r = (r+1<m ? r+1 : 0);
    }
    ll sub = (l < r ? area[r] : area[r + m]) - area[l];
    ll cur = base - sub + cross(inner[l], outer[i]) + cross(outer[i], inner[r]);
    ans = max(ans, cur);
  }

  cout << ans / 2 << "." << (ans % 2 == 0 ? 0 : 5) << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(1);
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

