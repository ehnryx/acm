//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "dominoes"

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

const int M = 18;
const int N = 30 + 7;
ll dp[1<<M], ndp[1<<M];
int h[M];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int m, n;
  cin >> m >> n;

  dp[0] = 1;
  for(int i=1; i<=n; i++) {
    memset(ndp, 0, sizeof ndp);
    for(int bm=(1<<(2*m))-1; bm>=0; bm--) {
      for(int j=0; j<m; j++) {
        h[j] = bm >> (2*j) & 3;
      }

      // invalid position
      if(*max_element(h, h+m) > i) {
        continue;
      }

      // use previous
      if(*min_element(h, h+m) > 0) {
        int sub = 0;
        for(int j=0; j<m; j++) {
          sub |= 1 << (2*j);
        }
        ndp[bm] = dp[bm-sub];
        continue;
      }

      // transitions
      for(int j=0; j<m; j++) {
        if(h[j] == 0) {
          ndp[bm] += ndp[bm + (3<<(2*j))];
          if(j+2 < m && h[j+1] == 0 && h[j+2] == 0) {
            ndp[bm] += ndp[bm + (0b010101<<(2*j))];
          }
          break;
        }
      }
    }

    swap(dp, ndp);
  }

  cout << dp[0] << nl;

  return 0;
}
