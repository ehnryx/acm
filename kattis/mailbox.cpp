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

const int N = 10 + 1;
const int M = 100 + 1;
int dp[N][M][M];

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

  memset(dp, INF, sizeof dp);
  for(int j=0; j<M; j++) {
    dp[0][j][j] = 0;
  }
  for(int i=1; i<N; i++) {
    for(int l=M-1; l>=0; l--) {
      for(int r=l; r<M; r++) {
        if(l == r) {
          dp[i][l][r] = 0;
        } else {
          for(int k=l+1; k<=r; k++) {
            dp[i][l][r] = min(dp[i][l][r], k + max(dp[i-1][l][k-1], dp[i][k][r]));
          }
        }
      }
    }
  }

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    cout << dp[n][0][m] << nl;
  }

  return 0;
}
