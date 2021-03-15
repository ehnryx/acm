#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

pair<pt,pt> intersect(const pt& c1, const ld& r1, const pt& c2, const ld& r2) {
  ld len = abs(c1 - c2);
  ld d = (len*len + r1*r1 - r2*r2) / (2 * len);
  ld h = sqrt(max((ld)0, r1*r1 - d*d));
  pt dir = (c2 - c1) / len;
  return pair(c1 + dir*(d + pt(0,h)), c1 + dir*(d - pt(0,h)));
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;

  vector<pt> c(n);
  vector<ld> r(n);
  vector<vector<pair<ld,int>>> ranges(n);
  vector<bool> covered(n);

  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y >> r[i];
    c[i] = pt(x, y);
    ranges[i].emplace_back(M_PIl + EPS, 1);

    for(int j=0; j<i; j++) {
      if(covered[j]) continue;
      if(abs(c[i] - c[j]) > r[i] + r[j] - EPS) continue;
      if(abs(c[i] - c[j]) < abs(r[i] - r[j]) + EPS) {
        if(r[j] <= r[i]) {
          covered[j] = true;
        }
      } else {
        auto [a, b] = intersect(c[i], r[i], c[j], r[j]);
        ld diff = arg((b - c[j]) / (a - c[j]));
        if(diff < 0) {
          swap(a, b);
          diff = arg((b - c[j]) / (a - c[j]));
        }
        pt mid = c[j] + (a - c[j]) * sqrt((b - c[j]) / (a - c[j]));
        ld s, t;
        if(abs(mid - c[i]) < r[i]) {
          tie(s, t) = pair(arg(a - c[j]), arg(b - c[j]));
        } else {
          tie(s, t) = pair(arg(b - c[j]), arg(a - c[j]));
        }
        ranges[j].emplace_back(s, 1);
        ranges[j].emplace_back(t, -1);
        if(s > t) {
          ranges[j].emplace_back(-M_PIl, 1);
          ranges[j].emplace_back(M_PIl, -1);
        }
      }
    }
  }

  ld ans = 0;
  for(int i=0; i<n; i++) {
    if(covered[i]) continue;
    sort(ranges[i].begin(), ranges[i].end());
    ld pre = -M_PIl;
    int cur = 0;
    ld add = 0;
    for(auto [x, t] : ranges[i]) {
      if(cur == 0) {
        add += x - pre;
      }
      cur += t;
      pre = x;
    }
    ans += add * r[i];
  }
  cout << ans << nl;

  return 0;
}
