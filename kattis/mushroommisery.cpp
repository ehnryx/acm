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
typedef /*long*/ double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld sqr(ld x) {
  return x*x;
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

  int s, n;
  cin >> s >> n;
  vector<vector<pair<int,int>>> ranges(s);
  for(int i=0; i<n; i++) {
    ld x, y, r;
    cin >> x >> y >> r;
    for(int j=0; j<s; j++) {
      if(j+1 <= x - r || x + r <= j) continue;
      ld d = 0;
      if(j < x && x < j+1) {
        d = r;
      } else if(x <= j) {
        d = sqrt(sqr(r) - sqr(j-x));
      } else {
        d = sqrt(sqr(r) - sqr(j+1-x));
      }
      int lb = floor(y - d + EPS);
      int ub = ceil(y + d - EPS);
      ranges[j].emplace_back(max(0, lb), min(s, ub));
    }
  }

  ll ans = 0;
  for(auto& v : ranges) {
    sort(v.begin(), v.end());
    int t = -INF;
    for(auto [a, b] : v) {
      if(a <= t) {
        if(b > t) {
          ans += b - t;
          t = b;
        }
      } else {
        ans += b - a;
        t = b;
      }
    }
  }
  cout << ans << nl;

  return 0;
}
