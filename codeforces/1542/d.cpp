#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/number/mod_int.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;
pair<Int, Int> operator + (const pair<Int, Int>& a, const pair<Int, Int>& b) {
  return pair(a.first + b.first, a.second + b.second);
}
pair<Int, Int>& operator += (pair<Int, Int>& a, const pair<Int, Int>& b) {
  a.first += b.first;
  a.second += b.second;
  return a;
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
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    char t;
    cin >> t;
    if(t == '-') {
      a[i] = -1;
    } else {
      cin >> a[i];
    }
  }
  a.push_back(numeric_limits<int>::max());

  vector<pair<int, int>> lbs;
  for(int s=0; s<=n; s++) {
    if(a[s] < 0) continue;
    lbs.emplace_back(a[s], s);
  }

  ll cnt = 0;
  Int ans = 0;
  for (const auto& lb : lbs) {
    cerr << nl;
    cerr << lb.first << " " << lb.second << nl;
    // position, # to remove, nonempty?
    vector dp(n+2, vector(n+2, vector<pair<Int, Int>>(2)));
    dp[0][0][0] = pair(Int(1), Int(0));
    for(int i=0; i<=n; i++) {
      for(int j=0; j<=n; j++) {
        for(int t=0; t<2; t++) {
          // skip
          if (pair(a[i], i) != lb && i < n) {
            dp[i+1][j][t] += dp[i][j][t];
          }
          // take
          if(a[i] < 0) {
            if(j > 0) {
              dp[i+1][j-1][t] += dp[i][j][t];
            } else if(j == 0 && t == 0) {
              dp[i+1][j][t] += dp[i][j][t];
            }
          } else if(pair(a[i], i) < lb) {
            dp[i+1][j+1][t] += dp[i][j][t];
          } else {
            dp[i+1][j][1] += dp[i][j][t];
            if (i+1 <= n) {
              dp[i+1][j][1].second += dp[i][j][t].first * a[i];
            }
          }
          cerr << "dp " << i << " " << j << " " << t << " :: " << dp[i][j][t].first << " " << dp[i][j][t].second  << nl;
        }
      }
      cerr << nl;
    }
    cnt += dp[n+1][0][1].first.value();
    assert(dp[n+1][0][0].first == 0);
    ans += dp[n+1][0][1].second;
    cerr << "got : " << dp[n+1][0][1].first.value() << nl;
    cerr << nl;
  }
  cout << ans << nl;
  cerr << "cnt: " << (cnt) << nl;

  return 0;
}
