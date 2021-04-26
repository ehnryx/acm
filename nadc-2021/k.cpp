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
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int M = 42 + 1;
ld pow2[M];

pair<ld,int> solve(int n, const vector<int>& a, const vector<int>& x, const ld& cost) {
  vector dp(n+1, vector<pair<ld,int>>(2)); // is the last one a station?
  for(int i=1; i<=n; i++) {
    dp[i][0] = dp[i-1][0]; // skip
    { // last one is a station
      ld val = 0;
      for(int j=0; j<i && x[i] - x[i-j] < M; j++) {
        if(j > 0) {
          val += a[i-j] / pow2[x[i] - x[i-j]];
        }
        dp[i][1] = max(dp[i][1], pair(dp[i-j-1][0].first + val, dp[i-j-1][0].second));
      }
    }
    { // last one may not be a station
      ld val = 0;
      for(int j=0; j<i && x[i] - x[i-j] < M; j++) {
        if(j > 0) {
          val /= pow2[x[i-j+1] - x[i-j]];
        }
        val += a[i-j];
        dp[i][0] = max(dp[i][0], pair(dp[i-j][1].first + val - cost, dp[i-j][1].second + 1));
      }
    }
  }
  return dp[n][0];
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(12);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  pow2[0] = 1;
  for(int i=1; i<M; i++) {
    pow2[i] = pow2[i-1] * 2;
  }

  int n, m;
  cin >> n >> m;
  vector<int> a(n+1), x(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i] >> x[i];
  }

  ld l = 0;
  ld r = 1e3;
  for(int bs=0; bs<42; bs++) {
    ld v = (l+r) / 2;
    int cnt = solve(n, a, x, v).second;
    if(cnt > m) {
      l = v;
    } else {
      r = v;
    }
  }
  cout << solve(n, a, x, r).first + r*m << nl;

  return 0;
}
