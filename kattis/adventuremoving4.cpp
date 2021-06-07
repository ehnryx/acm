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

  int m;
  cin >> m;
  vector<pair<int,int>> gas;
  for(int d, v; cin >> d >> v; ) {
    gas.emplace_back(d, v);
  }
  gas.emplace_back(m, 0);

  int n = size(gas);
  vector dp(n, vector<int>(200 + 1, -1));
  if(gas[0].first <= 100)  {
    dp[0][100 - gas[0].first] = 0;
  }
  for(int i=1; i<n; i++) {
    for(int j=0; j + gas[i].first - gas[i-1].first <= 200; j++) {
      for(int k=0; k <= j + gas[i].first - gas[i-1].first; k++) {
        if(dp[i-1][k] < 0) continue;
        if(dp[i][j] < 0 || dp[i-1][k] + (j + gas[i].first - gas[i-1].first - k) * gas[i-1].second < dp[i][j]) {
          dp[i][j] = dp[i-1][k] + (j + gas[i].first - gas[i-1].first - k) * gas[i-1].second;
        }
      }
    }
  }
  if(dp[n-1][100] < 0) {
    cout << "Impossible" << nl;
  } else {
    cout << dp[n-1][100] << nl;
  }

  return 0;
}
