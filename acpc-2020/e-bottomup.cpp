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

const int N = 51 * 9 + 1;
const int M = 1<<20;
short dp[2][M];
bitset<M> pre[N];
char grid[51][9];

bool update(short& x, short v) {
  x = min(x, v);
  return x == v;
}

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

  int n, m, k;
  cin >> n >> m >> k;
  const int L = 2*m + 4;
  const int clear = ~(1 << L);

  dp[0][0] = 0;
  for(int i=0; i<=n; i++) {
    for(int j=0; j<=m; j++) {
      memset(dp[1], INF, sizeof dp[1]);
      int u = i*(m+1) + j;
      for(int bm=0; bm<1<<L; bm++) {
        if(dp[0][bm] == (short)INF) continue;
        int rem = bm >> (L-1) & 1;
        int add = (bm << 1 & clear) | 1;
        int skip = (bm << 1 & clear);
        if((bm & 1<<(m+1)) || j == 0 || i == 0) {
          if(update(dp[1][add], dp[0][bm] + 1)) {
            pre[u+1][add] = rem;
          }
          if(update(dp[1][skip], dp[0][bm])) {
            pre[u+1][skip] = rem;
          }
        } else {
          int cnt = (bm & 1) + (bm >> (2*(m+1)) & 1);
          cnt += (bm >> m & 1) + (bm >> (2*m + 1) & 1);
          if(j > 1) {
            cnt += (bm >> 1 & 1) + (bm >> (m+2) & 1) + (bm >> (2*m+3) & 1);
          }
          if(cnt == k) {
            if(update(dp[1][skip], dp[0][bm])) {
              pre[u+1][skip] = rem;
            }
          } else if(cnt + 1 == k) {
            if(update(dp[1][add], dp[0][bm] + 1)) {
              pre[u+1][add] = rem;
            }
          }
        }
        if(i == n || j == m) {
          dp[1][add] = (short)INF;
        }
      }
      swap(dp[0], dp[1]);
    }
  }

  int t = (n+1) * (m+1);
  int bm = min_element(dp[0], dp[0]+M) - dp[0];
  cout << dp[0][bm] << nl;

  while(t--) {
    grid[t/(m+1)][t%(m+1)] = ((bm & 1) ? '#' : '.');
    bm = bm >> 1 | (int)pre[t+1][bm] << (L-1);
  }
  for(int j=0; j<m; j++) {
    for(int i=0; i<n; i++) {
      cout << grid[i][j];
    }
    cout << nl;
  }

  return 0;
}
