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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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

  int n, x, y, z, c, r;
  cin >> n >> x >> y >> z >> c >> r;
  vector<ld> dp(n+1);
  dp[0] = x;
  for(int i=1; i<=n; i++) {
    for(int j=0; j<i; j++) {
      ld donate = (ld)(i-j) * y;
      ld cur = dp[j] - donate;
      if(donate > z) {
        cur += (donate - z) * (ld)c/100;
      }
      dp[i] = max(dp[i], cur * pow(1 + (ld)r/100, i-j));
    }
  }
  cout << dp[n] << nl;

  return 0;
}
