#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma")

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
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



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
  ld c, d;
  cin >> c >> d;
  vector<int> rain(n);
  for(int i=0; i<n; i++) {
    cin >> rain[i];
  }
  vector<int> sum(1);
  partial_sum(begin(rain), end(rain), back_inserter(sum));

  ld ans = 1e42;
  for(int len=0; len<n; len++) {
    pair<int,int> best(INF, 0);
    for(int s=0; s+len<=n; s++) {
      int adj = INF;
      if(s > 0) adj = min(adj, rain[s-1]);
      if(s+len < n) adj = min(adj, rain[s+len]);
      best = min(best, pair(sum[s+len] - sum[s], adj));
    }

    function<ld(ld,int)> calc = [=](ld t, int r) {
      ld u = d / (t + len);
      ld v = (d - u*len) / t;
      u *= 60; // because km/h instead of km/min
      v *= 60; // because km/h instead of km/min
      return len * c*u*u + t*r + t * c*v*v;
    };

    ld l = 0;
    ld r = 1;
    for(int bs=0; bs<42; bs++) {
      ld lm = (5*l + 4*r) / 9;
      ld rm = (4*l + 5*r) / 9;
      ld lval = calc(lm, best.second);
      ld rval = calc(rm, best.second);
      if(lval < rval) {
        r = rm;
      } else {
        l = lm;
      }
    }
    ans = min(ans, best.first + calc((l+r)/2, best.second));
  }

  cout << ans << nl;

  return 0;
}
