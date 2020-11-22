//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 60 + 1;
const int M = 2000 + 7;
bool dp[N][M];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, g;
  cin >> n >> g;
  dp[0][0] = true;
  for(int i=1; i<=n; i++) {
    int d;
    cin >> d;
    for(int j=i; j>=1; j--) {
      for(int v=d; v<M; v++) {
        dp[j][v] |= dp[j-1][v-d];
      }
    }
  }

  ld ans = -2;
  for(int i=1; i<=n; i++) {
    for(int j=g-10; j<=g+5*(i-1); j++) {
      if(dp[i][j]) {
        ans = max(ans, (ld) (j - (g-10)) / (i + 1));
      }
    }
  }

  if(ans < -1) {
    cout << "impossible" << nl;
  } else {
    cout << ans << nl;
  }

  return 0;
}
