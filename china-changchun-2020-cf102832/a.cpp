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

  const vector<int> rmb = { 1, 6, 28, 88, 198, 328, 648 };
  const vector<int> bonus = { 8, 18, 28, 58, 128, 198, 388 };

  int n;
  cin >> n;
  vector dp(n+1, vector<int>(1<<7, -INF));
  dp[0][0b1'111'111] = 0;
  for(int i=1; i<=n; i++) {
    for(int bm=0; bm<1<<7; bm++) {
      for(int j=0; j<7 && rmb[j] <= i; j++) {
        int add = (bm & 1<<j) ? 0 : bonus[j];
        dp[i][bm] = max(dp[i][bm], dp[i-rmb[j]][bm | 1<<j] + add);
      }
    }
  }
  cout << *max_element(begin(dp[n]), end(dp[n])) + n*10 << nl;

  return 0;
}
